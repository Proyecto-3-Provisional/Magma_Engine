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

// Devuelve un puntero al Objeto creado, o nullptr si falla
GraphicalObject* RenderManager::addObject(std::string key, GraphicalObject* parent = nullptr,
	std::string mesh = "", std::string material = "default")
{
	// La estructura de diccionario "sceneObjects" ya comprobaba la existencia
	// de la clave, no a�adiendo el objeto en caso de que ya existiera.
	// 
	// Por desgracia, al construir un GraphicalObject indicando a otro como
	// padre, se anota un punto al contador de hijos de este padre, impidiendo
	// su posterior borrado (regla escrita en 'removeObject()').
	// 
	// Esto ocurr�a aun cuando el objeto hijo no acababa insertado en el diccionario
	// (me ha pasado al programar mal la tripulaci�n, no cambiando la clave para
	// cada tripulante, y hasta causando un bloqueo en la app a la salida), por
	// lo que he decidido comprobar con 'getObject()' (operaci�n 'at()') si la
	// clave ya est� en uso.
	// 
	// No empleo 'contains()' del diccionario, puesto que en el est�ndar en el
	// que se encuentra este proyecto no existe tal operaci�n.
	// 
	// Adem�s, la situaci�n de no a�adir al diccionario pese a llamar a 'new'
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

// Devuelve un puntero al Objeto, o nullptr si no se halla
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

// No devuelve nada
void RenderManager::sunsetObject(GraphicalObject* gO)
{
	sceneObjectsToRemove.push_back(gO);
}

// Devuelve si tuvo �xito el marcado (encolado)
bool RenderManager::sunsetObject(std::string key)
{
	// comprobar que existe la clave
	GraphicalObject* gO = getObject(key);
	if (!gO)
		return false;
	
	sceneObjectsToRemove.push_back(gO);
	return true;
}

// Devuelve si tuvo �xito (el Objeto no se resisti� a ser borrado)
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

// Devuelve si tuvo �xito (el Objeto se encontr� Y no se resisti� a ser borrado)
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

// POSIBLEMENTE BLOQUEANTE; No devuelve nada
void RenderManager::removeObjects()
{
	while (!sceneObjects.empty())
	{
		auto it = sceneObjects.begin();
		while (it != sceneObjects.end()) {
			// avanzar �ndice, pero dejando acceso tambi�n al Objeto a borrar
			auto it_aux = it;
			it++;
			
			// 1st es la key; 2nd es el ptr al Objeto
			// tratar de borrar
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

void RenderManager::setBgColor(float r, float g, float b)
{
	if (cam && vp)
	{
		vp->setBackgroundColour(Ogre::ColourValue(r, g, b));
	}
}

void RenderManager::setup(void)
{
	RenderManagerContext::setup(); // NO OLVIDAR; LO PRIMERO
	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);

	createPlaneMesh(); // <-> nos interesa disponer de esta malla

	setupScene(); // disponer la escena
}

// POSIBLEMENTE BLOQUEANTE debido a removeObjects()
void RenderManager::shutdown()
{
	removeObjects(); // Quitar todos aquellos cuerpos a�adidos a la escena

	mSM->removeRenderQueueListener(mOverlaySystem);
	mRoot->destroySceneManager(mSM);
	RenderManagerContext::shutdown(); // NO OLVIDAR
}

void RenderManager::setupScene(void)
{
	// create the camera
	cam = mSM->createCamera("Cam");
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
	vp = getRenderWindow()->addViewport(cam);
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));

	//------------------------------------------------------------------------

	// LUCES
	GraphicalObject* sol = addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.5, 0.5, 0.3);
	sol->setDirection({ 0, -0.8, -1 });
	//
	GraphicalObject* lbulb = addObject("bombilla", nullptr, "LIGHTBULB");
	lbulb->setLightColor(0.5, 0.5, 0.85);
	lbulb->setPosition({ 0, 500, 200 });
	//	
	GraphicalObject* spotl = addObject("foco", nullptr, "SPOTLIGHT");
	spotl->setLightColor(1.0, 0.2, 0.2);
	spotl->setPosition({ 0, 0, 500 });
	spotl->setPosition({ 0, 0.5, -1 });

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
	ajo->showDebugBox(false);
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
