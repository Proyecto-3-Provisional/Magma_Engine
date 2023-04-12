#include "render_manager.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <SDL_events.h>

std::unique_ptr<RenderManager> Singleton<RenderManager>::instance_;

// Recibe un booleano que indica si el cursor puede salir de la ventana o no
RenderManager::RenderManager(bool grabCursor) : RenderManagerContext("MagmaTest")
{
	bgColR = bgColG = bgColB = 0.0f;
	RenderManagerContext::cursorGrab = grabCursor;
	// CONTEXT: new -> setup()
}

// Recibe un booleano que indica si el cursor puede salir de la ventana o no
// y parámetros que modifican la ventana y las condiciones del renderizado
RenderManager::RenderManager(bool grabCursor, uint32_t w, uint32_t h, bool fScr,
	bool vSyn, int fsaa, bool gamm) : RenderManagerContext("MagmaTest", w, h,
	fScr, vSyn, fsaa, gamm)
{
	bgColR = bgColG = bgColB = 0.0f;
	RenderManagerContext::cursorGrab = grabCursor;
	// CONTEXT: new -> setup()
}

RenderManager::~RenderManager()
{
	// CONTEXT: delete -> shutdown()
}

void RenderManager::setCamPos(Ogre::Vector3 vec)
{
	if (cameraNode)
		cameraNode->setPosition(vec);
}

void RenderManager::translateCam(Ogre::Vector3 vec, Ogre::Node::TransformSpace relTo)
{
	if (cameraNode)
		cameraNode->translate(vec, relTo);
}

void RenderManager::setCamOrientation(float ang, Ogre::Vector3 axis)
{
	if (cameraNode)
	{
		Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(ang), Ogre::Vector3(axis));
		cameraNode->setOrientation(q);
	}
}

void RenderManager::yawCam(float deg, Ogre::Node::TransformSpace relTo)
{
	if (cameraNode)
		cameraNode->yaw(Ogre::Degree(deg), relTo);
}

void RenderManager::pitchCam(float deg, Ogre::Node::TransformSpace relTo)
{
	if (cameraNode)
		cameraNode->pitch(Ogre::Degree(deg), relTo);
}

void RenderManager::rollCam(float deg, Ogre::Node::TransformSpace relTo)
{
	if (cameraNode)
		cameraNode->roll(Ogre::Degree(deg), relTo);
}

void RenderManager::setCamLookAt(Ogre::Vector3 vec, Ogre::Node::TransformSpace relTo,
	Ogre::Vector3 lDirVec)
{
	if (cameraNode)
		cameraNode->lookAt(vec, relTo, lDirVec);
}

// 0. Comprobar que no hay cámara
// 1. Crear nodo para la cámara
// 2. Crear la cámara y asignarle su nodo
// 3. Configurar cámara
// 4. Crear puerto de vista
void RenderManager::createCam(GraphicalObject* follow, Ogre::Vector3 startPos)
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

	camera->setNearClipDistance(1);		//
	camera->setFarClipDistance(10000);	//
	camera->setAutoAspectRatio(true);	//
	setCamPos(startPos);
	if (cameraFollows)
		setCamLookAt({ 0, 0, 1000 }, Ogre::Node::TS_LOCAL);
	else
		setCamLookAt({ 0, 0, 0 }, Ogre::Node::TS_WORLD);

	cameraViewport = getRenderWindow()->addViewport(camera);
}

// 0. Comprobar que hay cámara
// 1. Destruir puerto de vista
// 2. Desasignar y destruir cámara
// 3. Destruir nodo y notificarlo
// 4. La cámara no sigue a nadie porque se ha borrado
void RenderManager::destroyCam()
{// que pasa si la cámara va en un objeto que muere?
	if (!camera && !cameraNode && !cameraViewport)
		return;

	getRenderWindow()->removeAllViewports();
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
// Se crea el objeto solo si la clave no está en uso
/* La estructura de diccionario "sceneObjects" ya comprobaba la existencia
de la clave, no añadiendo el objeto en caso de que ya existiera.
Pese a esto, para saber si el objeto no debería ser construido, lo
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
// Se comprueba básicamente que la clave exista en el diccionario
GraphicalObject* RenderManager::getObject(std::string key)
{
	GraphicalObject* gO = nullptr;
	try
	{
		gO = sceneObjects.at(key);
	}
	catch (std::out_of_range e) { }
	return gO;
}

// No devuelve nada
void RenderManager::sunsetObject(GraphicalObject* gO)
{
	sceneObjectsToRemove.push_back(gO);
}

// Devuelve si tuvo éxito el marcado (encolado)
// La clave debe existir en el diccionario
bool RenderManager::sunsetObject(std::string key)
{
	GraphicalObject* gO = getObject(key);
	if (!gO)
		return false;
	sceneObjectsToRemove.push_back(gO);
	return true;
}

// Devuelve si tuvo éxito (el Objeto no se resistió a ser borrado)
// Un objeto se resiste cuando de él pende algún objeto hijo
// ¡Comprobar que el puntero sea válido!
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

// Devuelve si tuvo éxito (el Objeto se encontró Y no se resistió a ser borrado)
// La clave debe existir en el diccionario
// Un objeto se resiste cuando de él pende algún objeto hijo
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
			// avanzar índice, pero dejando acceso también al Objeto a borrar
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

// De todos los objetos gráficos, ver cuáles son entidades de Ogre y
// hacer avanzar su animación si es que existe
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

// Al final crea la malla de un plano por código
// NO CAMBIAR LA PRIMERA LÍNEA
void RenderManager::setup()
{
	RenderManagerContext::setup();

	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);

	createPlaneMesh();
}

// POSIBLEMENTE BLOQUEANTE debido a removeObjects() -> Destruir cámara antes
// 'removeObjects' quita todos aquellos objetos añadidos a la escena
// 'removeObjects' puede ejecutarse tanto antes como después de 'destroyCam'
// NO CAMBIAR LA ÚLTIMA LÍNEA
void RenderManager::shutdown()
{
	removeObjects();
	destroyCam();

	mSM->removeRenderQueueListener(mOverlaySystem);
	mRoot->destroySceneManager(mSM);

	RenderManagerContext::shutdown();
}

// Definir malla mPlane1080x800
void RenderManager::createPlaneMesh(Ogre::String name)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), // vector normal, vector up
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
}

// Usado en la práctica para desanclar la cámara de la jerarquía de objetos
void RenderManager::replaceCam()
{
	destroyCam();
	createCam(nullptr);
	setBgColor(bgColR, bgColG, bgColB);
}
