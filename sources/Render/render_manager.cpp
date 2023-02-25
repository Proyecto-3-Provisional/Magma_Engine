#include "render_manager.h"

#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreViewport.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#include <SDL_events.h>

render_manager::render_manager() : render_manager_context("MagmaTest"),
	keydown(false), rotationVelocity(0.05)
{
}

render_manager::~render_manager()
{
}

void render_manager::rotate(float deltaTime)
{
	mCubeNode->yaw(Ogre::Degree(rotationVelocity * deltaTime));
	mCrewNode->roll(Ogre::Degree(rotationVelocity * deltaTime) * -1);
}

void render_manager::setup(void)
{
	render_manager_context::setup(); // NO OLVIDAR; LO PRIMERO
	mSM = mRoot->createSceneManager();
	mSM->addRenderQueueListener(mOverlaySystem);
	setupScene();
}

void render_manager::shutdown()
{
  mSM->removeRenderQueueListener(mOverlaySystem);
  mRoot->destroySceneManager(mSM);
  render_manager_context::shutdown(); // NO OLVIDAR
}

void render_manager::setupScene(void)
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
  Ogre::Entity* cube = mSM->createEntity("axolotl.mesh"); // crear entidad
  cube->setMaterialName("axolotl"); // definir material de la entidad

  mCubeNode = mSM->getRootSceneNode()->createChildSceneNode("CubeNode"); // crear nodo, hijo del 'raíz'
  mCubeNode->attachObject(cube); // anclar entidad a nodo
  
  // configurar nodo
  mCubeNode->setPosition(0, 0, 50); // me lo acerco a la cara 50 ud.
  mCubeNode->setScale(40, 40, 40);
  mCubeNode->yaw(Ogre::Degree(-45));
  mCubeNode->showBoundingBox(false);
  mCubeNode->setVisible(true);

  // Tripulantes
  mCrewNode = mSM->getRootSceneNode()->createChildSceneNode("CrewNode");
  mCrewNode->setPosition(0, 0, 50);
  mCrewNode->setScale(100, 100, 100);

  float delta_degrees = 360 / NUM_CREWMATES;
  float init_degrees = 90;
  float degrees = init_degrees;
  float radius = 3;
  for (size_t i = 0; i < NUM_CREWMATES; i++)
  {
	  Ogre::SceneNode* n = mSM->getSceneNode("CrewNode")->createChildSceneNode();
	  n->setPosition(Ogre::Vector3(
		  radius * Ogre::Math::Cos(Ogre::Degree(degrees)),
		  radius * Ogre::Math::Sin(Ogre::Degree(degrees)),
		  0));
	  n->setOrientation(Ogre::Quaternion(Ogre::Degree(degrees - init_degrees), Ogre::Vector3(0, 0, 1)));

	  mCrew[i] = mSM->createEntity("amongus.mesh"); // crear entidad
	  mCrew[i]->setMaterialName(crew_colors[i]);
	  n->attachObject(mCrew[i]);

	  degrees -= delta_degrees;
  }

  // PLANO
  // definir malla mPlane1080x800
  Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
	  Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	  Ogre::Plane(Ogre::Vector3::UNIT_Z, 0), // vector normal, vector up
	  1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_Y);
  // crear entidad
  Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
  plane->setMaterialName("default");
  // crear nodo
  mPlaneNode = mSM->getRootSceneNode()->createChildSceneNode("PlaneNode");
  mPlaneNode->attachObject(plane);
  mPlaneNode->setPosition(0, 0, -400);
}

void render_manager::pollEvents() // from frameStarted
{
	if (mWindow.native == nullptr)
		return;  // SDL events not initialized

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT: // CRUZ DE CERRAR VENTANA
			// Esto hace que el bucle de main() se detenga
			exitRequest = true;
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(mWindow.native))
			{
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = mWindow.render;
					win->windowMovedOrResized();
					windowResized(win);
				}
			}
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				// SE PULSA LA TECLA 'ESCAPE'
				exitRequest = true;
			}
			else
			{
				if (!keydown)
				{
					keydown = true;
					rotationVelocity += 0.1;
				}
			}
			break;
		case SDL_KEYUP:
			if (keydown)
			{
				keydown = false;
				rotationVelocity = 0.05;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				rotationVelocity += 0.1;
			}
			else if (event.button.button == SDL_BUTTON_RIGHT) {
				rotationVelocity -= 0.1;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			rotationVelocity = 0.05;
			break;
		default:
			break;
		}
	}
}
