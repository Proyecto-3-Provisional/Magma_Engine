#include "render_manager.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <SDL_events.h>

RenderManager::RenderManager() : RenderManagerContext("MagmaTest")
{
}

RenderManager::~RenderManager()
{
}

// Devuelve un puntero al objeto creado, o nullptr si falla
GraphicalObject* RenderManager::addObject(std::string key, GraphicalObject* parent = nullptr,
	std::string mesh = "", std::string material = "default")
{
	// La estructura de diccionario "sceneObjects" ya comprobaba la existencia
	// de la clave, no añadiendo el objeto en caso de que ya existiera.
	// 
	// Por desgracia, al construir un GraphicalObject indicando a otro como
	// padre, se anota un punto al contador de hijos de este padre, impidiendo
	// su posterior borrado (regla escrita en 'removeObject()').
	// 
	// Esto ocurría aun cuando el objeto hijo no acababa insertado en el diccionario
	// (me ha pasado al programar mal la tripulación, no cambiando la clave para
	// cada tripulante, y hasta causando un bloqueo en la app a la salida), por
	// lo que he decidido comprobar con 'getObject()' (operación 'at()') si la
	// clave ya está en uso.
	// 
	// No empleo 'contains()' del diccionario, puesto que en el estándar en el
	// que se encuentra este proyecto no existe tal operación.
	// 
	// Además, la situación de no añadir al diccionario pese a llamar a 'new'
	// implicaba fugas de memoria...

	// comprobar clave...
	GraphicalObject* gO = getObject(key);
	if (gO)
		return nullptr;

	// crear objeto solo si la clave es nueva
	GraphicalObject* newGO = new GraphicalObject(key, *mSM, parent, mesh, material);
	sceneObjects.insert(std::make_pair(key, newGO));

	return newGO;
}

// Devuelve nullptr si no se halla
GraphicalObject* RenderManager::getObject(std::string key)
{
	// Hay que comprobar que existe la clave
	GraphicalObject* gO = nullptr;
	try
	{
		gO = sceneObjects.at(key);
	}
	catch (std::out_of_range e)
	{
	}
	return gO;
}

// No devuelve NADA
void RenderManager::sunsetObject(GraphicalObject* gO)
{
	sceneObjectsToRemove.push_back(gO);
}

// Devuelve si tuvo éxito (el marcado)
bool RenderManager::sunsetObject(std::string key)
{
	// comprobar que existe la clave
	GraphicalObject* gO = getObject(key);
	if (!gO)
		return false;
	
	sceneObjectsToRemove.push_back(gO);
	return true;
}

// Devuelve si tuvo éxito
bool RenderManager::removeObject(GraphicalObject* gO)
{
	// si de este objeto penden otros, no hacer nada
	if (gO->getChildrenUsing() > 0)
		return false;

	// borrar objeto
	sceneObjects.erase(gO->getKeyName());
	delete gO;
	gO = nullptr;
	return true;
}

// Devuelve si tuvo éxito
bool RenderManager::removeObject(std::string key)
{
	// comprobar que existe la clave
	GraphicalObject* gO = getObject(key);
	if (!gO)
		return false;

	// si de este objeto penden otros, no hacer nada
	if (gO->getChildrenUsing() > 0)
		return false;

	// borrar objeto
	delete gO;
	gO = nullptr;
	sceneObjects.erase(key);
	return true;
}

// No devuelve NADA
// Si se programa algo mal, puede haber un bloqueo -> while(1)
void RenderManager::removeObjects() // Este algoritmo es algo inquietante
{
	while (!sceneObjects.empty())
	{
		auto it = sceneObjects.begin();
		while (it != sceneObjects.end()) {
			// avanzar índice, pero dejandome acceso también al que quiero borrar
			auto it_aux = it;
			it++;
			
			// 1st es la key; 2nd es el ptr al Objeto
			// tratar de borrar
			/*bool b = */removeObject((*it_aux).second);
		}
	}
}

// Devuelve verdadero solo si ningún objeto se resistió a ser borrado (tiene hijos)
bool RenderManager::refreshObjects()
{
	bool ret = true;

	auto it = sceneObjectsToRemove.begin();
	while (it != sceneObjectsToRemove.end()) {
		// avanzar índice, pero dejandome acceso también al que quiero borrar
		auto it_aux = it;
		it++;

		// tratar de borrar
		bool b = removeObject((*it_aux));
		if (b)
			sceneObjectsToRemove.erase(it_aux);
		ret = ret && b;
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

void RenderManager::setup(void)
{
	RenderManagerContext::setup(); // NO OLVIDAR; LO PRIMERO
	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);

	createPlaneMesh(); // <-> nos interesa disponer de esta malla

	setupScene(); // disponer la escena
}

void RenderManager::shutdown()
{
	removeObjects(); // Quitar todos aquellos cuerpos añadidos a la escena

	mSM->removeRenderQueueListener(mOverlaySystem);
	mRoot->destroySceneManager(mSM);
	RenderManagerContext::shutdown(); // NO OLVIDAR
}

void RenderManager::setupScene(void)
{
	// create the camera
	Ogre::Camera* cam = mSM->createCamera("Cam");
	cam->setNearClipDistance(1);
	cam->setFarClipDistance(10000);
	cam->setAutoAspectRatio(true);
	//cam->setPolygonMode(Ogre::PM_WIREFRAME); 

	mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
	mCamNode->attachObject(cam);

	mCamNode->setPosition(0, 0, 1000);
	mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
	//mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  

	// and tell it to render into the main window
	Ogre::Viewport* vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Ogre::Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.90, 0.90, 0.90);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
	//lightNode->setPosition(0, 0, 1000);

	//------------------------------------------------------------------------

	// CUBO
	GraphicalObject* aux = addObject("cube_empty");
	aux->setPosition({ 0, 0, 50 });
	aux->setScale({ 0.8, 0.8, 0.8 });
	aux->makeVisible(true);
	//
	GraphicalObject* cubo = addObject("cube", aux, "cube.mesh", "logo");
	cubo->translate({ 0, 0, 200 }, Ogre::Node::TransformSpace::TS_WORLD);

	// AJOLOTE
	GraphicalObject* ajo = addObject("suxalote", nullptr, "axolotl.mesh", "axolotl");
	ajo->showDebugBox(true);
	ajo->setPosition({ 0, 0, 50 }); // me lo acerco a la cara 50 ud.
	ajo->setScale({ 40, 40, 40 });

	// TRIPULANTES
	GraphicalObject* rosco = addObject("crew", nullptr, "", "thiswontbeused");
	rosco->setPosition({ 0, 0, 50 });
	rosco->setScale({ 100, 100, 100 });
	//
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

void RenderManager::createPlaneMesh(Ogre::String name)
{
	// definir malla mPlane1080x800
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), // vector normal, vector up
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
}
