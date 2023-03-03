#include "render_manager.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <SDL_events.h>

// Recibe un booleano que indica si el cursor puede salir de la ventana o no
RenderManager::RenderManager(bool grabCursor) : RenderManagerContext("MagmaTest")
{
	RenderManagerContext::cursorGrab = grabCursor;

	// CONTEXT:
	// new -> setup()
}

RenderManager::~RenderManager()
{
	// CONTEXT:
	// delete -> shutdown()
}

// Devuelve un puntero al Objeto creado, o nullptr si falla
// Se crea el objeto solo si la clave no está en uso
/* La estructura de diccionario "sceneObjects" ya comprobaba la existencia
de la clave, no añadiendo el objeto en caso de que ya existiera.
Pese a esto, para saber si el objeto no debería ser construido, lo
comprobamos manualmente de todos modos. Tampoco disponemos de 'contains()' */
GraphicalObject* RenderManager::addObject(std::string key, GraphicalObject* parent = nullptr,
	std::string mesh = "", std::string material = "default")
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
bool RenderManager::removeObject(GraphicalObject* gO)
{
	if (gO->getChildrenUsing() > 0)
		return false;
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
	if (gO->getChildrenUsing() > 0)
		return false;
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
bool RenderManager::refreshObjects()
{
	int ret = 0;
	while (!sceneObjectsToRemove.empty())
	{
		if (!removeObject(sceneObjectsToRemove.front())) ret++;
		sceneObjectsToRemove.pop_front();
	}
	return ret;
}

int RenderManager::getNumObjects()
{
	return sceneObjects.size();
}

int RenderManager::getNumObjectsToRemove()
{
	return sceneObjectsToRemove.size();
}

void RenderManager::objectShowMode(int val)
{
	if (cam)
	{
		if (val == 1)
		{
			cam->setPolygonMode(Ogre::PM_WIREFRAME); 
		}
		else if (val == 2)
		{
			cam->setPolygonMode(Ogre::PM_POINTS);
		}
		else
		{
			cam->setPolygonMode(Ogre::PM_SOLID);
		}
	}
}

void RenderManager::setBgColor(float r, float g, float b)
{
	if (cam && vp)
	{
		vp->setBackgroundColour(Ogre::ColourValue(r, g, b));
	}
}

// Al final crea la malla de un plano po código y dispone la escena
// NO CAMBIAR LA PRIMERA LÍNEA
void RenderManager::setup()
{
	RenderManagerContext::setup();

	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);

	createPlaneMesh();
	setupScene();
}

// POSIBLEMENTE BLOQUEANTE debido a removeObjects()
// removeObjects quita todos aquellos objetos añadidos a la escena
// NO CAMBIAR LA ÚLTIMA LÍNEA
void RenderManager::shutdown()
{
	removeObjects();

	mSM->removeRenderQueueListener(mOverlaySystem);
	mRoot->destroySceneManager(mSM);

	RenderManagerContext::shutdown();
}

// Se crean la cámara y los objetos de prueba
void RenderManager::setupScene(void)
{
	// CÁMARA
	cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	mCamNode = mSM->getRootSceneNode()->createChildSceneNode();
	mCamNode->attachObject(cam);
	vp = getRenderWindow()->addViewport(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);

	// LUCES
	GraphicalObject* sol = addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.5, 0.5, 0.3);
	sol->setDirection({ 0, -0.8, -1 });
	GraphicalObject* lbulb = addObject("bombilla", nullptr, "LIGHTBULB");
	lbulb->setLightColor(0.5, 0.5, 0.85);
	lbulb->setPosition({ 0, 500, 200 });
	GraphicalObject* spotl = addObject("foco", nullptr, "SPOTLIGHT");
	spotl->setLightColor(1.0, 0.2, 0.2);
	spotl->setPosition({ 0, 0, 500 });
	spotl->setPosition({ 0, 0.5, -1 });

	// CUBO
	GraphicalObject* aux = addObject("cube_empty");
	aux->setPosition({ 0, 0, 50 });
	aux->setScale({ 0.8, 0.8, 0.8 });
	aux->makeVisible(true);
	GraphicalObject* cubo = addObject("cube", aux, "cube.mesh", "logo");
	cubo->translate({ 0, 0, 200 }, Ogre::Node::TransformSpace::TS_WORLD);

	// AJOLOTE con emisor de partículas
	GraphicalObject* ajo = addObject("suxalote", nullptr, "axolotl.mesh", "axolotl");
	ajo->showDebugBox(false);
	ajo->setPosition({ 0, 0, 50 }); // me lo acerco a la cara 50 ud.
	ajo->setScale({ 40, 40, 40 });
	GraphicalObject* burst = addObject("bubbles", ajo, "EMITTER", "bubble_burst");
	burst->translate({ 5, 0, 0 });

	// TRIPULANTES
	GraphicalObject* rosco = addObject("crew", nullptr, "", "thiswontbeused");
	rosco->setPosition({ 0, 0, 50 });
	rosco->setScale({ 100, 100, 100 });
	float delta_degrees = 360 / NUM_CREWMATES;
	float init_degrees = 90;
	float degrees = init_degrees;
	float radius = 3;
	for (size_t i = 0; i < NUM_CREWMATES; i++)
	{
		GraphicalObject* tripulante = addObject(
			"crewmate_" + crew_colors[i], rosco, "amongus.mesh", crew_colors[i]);
		Ogre::Vector3 p = {
			radius * Ogre::Math::Cos(Ogre::Degree(degrees)),
			radius * Ogre::Math::Sin(Ogre::Degree(degrees)),
			0 };
		tripulante->setPosition(p);
		tripulante->setOrientation(degrees - init_degrees, { 0, 0, 1 });

		degrees -= delta_degrees;
	}

	// PLANO
	GraphicalObject* plano = addObject("bckgrnd_plane", nullptr, "mPlane1080x800");
	plano->setPosition({ 0, 0, -400 });
}

// Definir malla mPlane1080x800
void RenderManager::createPlaneMesh(Ogre::String name)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), // vector normal, vector up
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
}
