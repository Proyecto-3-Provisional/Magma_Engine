#include <Render/render_manager.h>
#include <Render/graphical_object.h>
#include <Render/render_manager_context.h>

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <SDL_events.h>

namespace magma_engine
{
	// Recibe un booleano que indica si el cursor puede salir de la ventana o no
	RenderManager::RenderManager(bool grabCursor)
	{
		context = new RenderManagerContext("MagmaTest");
		bgColR = bgColG = bgColB = 0.0f;
		context->setCursor(grabCursor);
		// CONTEXT: new -> setup()
	}

	// Recibe un booleano que indica si el cursor puede salir de la ventana o no
	// y par�metros que modifican la ventana y las condiciones del renderizado
	RenderManager::RenderManager(bool grabCursor, uint32_t w, uint32_t h, bool fScr,
		bool vSyn, int fsaa, bool gamm)
	{
		context = new RenderManagerContext("MagmaTest", w, h, fScr, vSyn, fsaa, gamm);
		bgColR = bgColG = bgColB = 0.0f;
		context->setCursor(grabCursor);
		// CONTEXT: new -> setup()
	}

	RenderManager::~RenderManager()
	{
		delete context;
	}

	void RenderManager::setCamPos(const Vector3D& vec)
	{
		if (cameraNode)
			cameraNode->setPosition(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()));
	}

	void RenderManager::translateCam(const Vector3D& vec)
	{
		if (cameraNode)
			cameraNode->translate(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void RenderManager::setCamOrientation(float ang, const Vector3D& axis)
	{
		if (cameraNode)
		{
			Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(ang), Ogre::Vector3(axis.getX(), axis.getY(), axis.getZ()));
			cameraNode->setOrientation(q);
		}
	}

	void RenderManager::yawCam(float deg)
	{
		if (cameraNode)
			cameraNode->yaw(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void RenderManager::pitchCam(float deg)
	{
		if (cameraNode)
			cameraNode->pitch(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void RenderManager::rollCam(float deg)
	{
		if (cameraNode)
			cameraNode->roll(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void RenderManager::setCamLookAt(const Vector3D& vec, const Vector3D& lDirVec)
	{
		if (cameraNode)
			cameraNode->lookAt(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()),
				Ogre::Node::TransformSpace::TS_WORLD,
				Ogre::Vector3(lDirVec.getX(), lDirVec.getY(), lDirVec.getZ()));
	}

	// 0. Comprobar que no hay c�mara
	// 1. Crear nodo para la c�mara
	// 2. Crear la c�mara y asignarle su nodo
	// 3. Configurar c�mara
	// 4. Crear puerto de vista
	void RenderManager::createCam(GraphicalObject* follow, const Vector3D& startPos)
	{
		if (camera && cameraNode && cameraViewport)
			return;

		cameraFollows = follow;
		if (cameraFollows)
		{
			cameraNode = cameraFollows->getNode()->createChildSceneNode();
			cameraFollows->setCamAttached(true);
		}
		else
		{
			cameraNode = mSM->getRootSceneNode()->createChildSceneNode();
		}

		camera = mSM->createCamera("MagmaCamera");
		cameraNode->attachObject(camera);

		camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
		camera->setNearClipDistance(1);		//
		camera->setFarClipDistance(10000);	//
		camera->setAutoAspectRatio(true);	//
		setCamPos(startPos);
		setCamLookAt({ 0, 0, 0 });
		if (cameraFollows)
			setCamLookAt({ startPos.getX(), startPos.getY(), startPos.getZ() - 1000 });

		cameraViewport = context->getRenderWindow()->addViewport(camera);
	}

	// 0. Comprobar que hay c�mara
	// 1. Destruir puerto de vista
	// 2. Desasignar y destruir c�mara
	// 3. Destruir nodo y notificarlo
	// 4. La c�mara no sigue a nadie porque se ha borrado
	void RenderManager::destroyCam()
	{// que pasa si la c�mara va en un objeto que muere?
		if (!camera && !cameraNode && !cameraViewport)
			return;

		context->getRenderWindow()->removeAllViewports();
		cameraViewport = nullptr;

		cameraNode->detachObject(camera);
		mSM->destroyCamera(camera);
		camera = nullptr;

		mSM->destroySceneNode(cameraNode);
		cameraNode = nullptr;
		if (cameraFollows)
			cameraFollows->setCamAttached(false);

		cameraFollows = nullptr; // No hacer delete de cameraFollows
	}

	// Devuelve un puntero al Objeto creado, o nullptr si falla
	// Se crea el objeto solo si la clave no est� en uso
	/* La estructura de diccionario "sceneObjects" ya comprobaba la existencia
	de la clave, no a�adiendo el objeto en caso de que ya existiera.
	Pese a esto, para saber si el objeto no deber�a ser construido, lo
	comprobamos manualmente de todos modos. Tampoco disponemos de 'contains()' */
	GraphicalObject* RenderManager::addObject(std::string key, GraphicalObject* parent,
		std::string mesh, std::string material)
	{
		GraphicalObject* gO = getObject(key);
		if (gO)
			return nullptr;
		GraphicalObject* newGO = new GraphicalObject(key, *mSM, parent, mesh, material);
		sceneObjects.insert(std::make_pair(key, newGO));
		return newGO;
	}

	// Devuelve un puntero al Objeto, o nullptr si no se halla
	// Se comprueba b�sicamente que la clave exista en el diccionario
	GraphicalObject* RenderManager::getObject(std::string key)
	{
		GraphicalObject* gO = nullptr;
		try
		{
			gO = sceneObjects.at(key);
		}
		catch (std::out_of_range e) {}
		return gO;
	}

	// No devuelve nada
	void RenderManager::sunsetObject(GraphicalObject* gO)
	{
		sceneObjectsToRemove.push_back(gO);
	}

	// Devuelve si tuvo �xito el marcado (encolado)
	// La clave debe existir en el diccionario
	bool RenderManager::sunsetObject(std::string key)
	{
		GraphicalObject* gO = getObject(key);
		if (!gO)
			return false;
		sceneObjectsToRemove.push_back(gO);
		return true;
	}

	// Devuelve si tuvo �xito (el Objeto no se resisti� a ser borrado)
	// Un objeto se resiste cuando de �l pende alg�n objeto hijo
	// �Comprobar que el puntero sea v�lido!
	bool RenderManager::removeObject(GraphicalObject* gO)
	{
		if (!gO)
			return false;
		if (gO->getChildrenUsing() > 0)
			return false;
		if (gO->isCamAttached())
			replaceCam();
		sceneObjects.erase(gO->getKeyName());
		delete gO;
		gO = nullptr;
		return true;
	}

	// Devuelve si tuvo �xito (el Objeto se encontr� Y no se resisti� a ser borrado)
	// La clave debe existir en el diccionario
	// Un objeto se resiste cuando de �l pende alg�n objeto hijo
	bool RenderManager::removeObject(std::string key)
	{
		GraphicalObject* gO = getObject(key);
		if (!gO)
			return false;
		else if (gO->getChildrenUsing() > 0)
			return false;
		if (gO->isCamAttached())
			replaceCam();
		delete gO;
		gO = nullptr;
		sceneObjects.erase(key);
		return true;
	}

	// No devuelve nada
	// POSIBLEMENTE BLOQUEANTE
	// Pares del diccionario:
	//	- 1st es la key
	//	- 2nd es el puntero al Objeto
	void RenderManager::removeObjects()
	{
		while (!sceneObjects.empty())
		{
			auto it = sceneObjects.begin();
			while (it != sceneObjects.end()) {
				// avanzar �ndice, pero dejando acceso tambi�n al Objeto a borrar
				auto it_aux = it;
				it++;
				/*bool b = */removeObject((*it_aux).second);
			}
		}
	}

	// Devuelve la cantidad de Objetos que se resistieron a ser borrados
	// Tales objetos quedan de todos modos desencolados...
	int RenderManager::refreshObjects()
	{
		int ret = 0;
		while (!sceneObjectsToRemove.empty())
		{
			if (!removeObject(sceneObjectsToRemove.front()))
				ret++;
			sceneObjectsToRemove.pop_front();
		}
		return ret;
	}

	int RenderManager::getNumObjects()
	{
		return (int)sceneObjects.size();
	}

	int RenderManager::getNumObjectsToRemove()
	{
		return (int)sceneObjectsToRemove.size();
	}

	/*
	 PM_POINTS		1
	 PM_WIREFRAME	2
	 PM_SOLID		3
	*/
	void RenderManager::objectShowMode(unsigned int val)
	{
		if (camera)
			camera->setPolygonMode((Ogre::PolygonMode)val);
	}

	void RenderManager::setBgColor(float r, float g, float b)
	{
		if (cameraViewport)
		{
			cameraViewport->setBackgroundColour(Ogre::ColourValue(r, g, b));
			bgColR = r; bgColG = g; bgColB = b;
		}
	}

	// De todos los objetos gr�ficos, ver cu�les son entidades de Ogre y
	// hacer avanzar su animaci�n si es que existe
	void RenderManager::stepAnimations(int deltaTime)
	{
		for (std::pair<std::string, GraphicalObject*> key_obj : sceneObjects)
		{
			if (key_obj.second->isEntityAnimated())
			{
				key_obj.second->stepAnimation(deltaTime * 0.001f);
			}
		}
	}

	bool RenderManager::renderFrame()
	{
		return context->renderFrame();
	}

	void RenderManager::notifyWindowResized()
	{
		context->notifyWindowResized();
	}

	bool RenderManager::initApp()
	{
		mSM = context->initApp();
		return mSM != nullptr;
	}

	void RenderManager::closeApp()
	{
		context->closeApp();
	}

	int RenderManager::getWinWidth()
	{
		return context->getWinWidth();
	}

	int RenderManager::getWinHeight()
	{
		return context->getWinHeight();
	}

	// POSIBLEMENTE BLOQUEANTE debido a removeObjects() -> Destruir c�mara antes
	// 'removeObjects' quita todos aquellos objetos a�adidos a la escena
	// 'removeObjects' puede ejecutarse tanto antes como despu�s de 'destroyCam'
	// NO CAMBIAR LA �LTIMA L�NEA
	void RenderManager::shutdown()
	{
		removeObjects();
		destroyCam();

		mSM->removeRenderQueueListener(context->getOverlaySystem());
		context->getRoot()->destroySceneManager(mSM);

		context->shutdown();
	}

	// Usado en la pr�ctica para desanclar la c�mara de la jerarqu�a de objetos
	void RenderManager::replaceCam()
	{
		destroyCam();
		createCam(nullptr);
		setBgColor(bgColR, bgColG, bgColB);
	}
}

