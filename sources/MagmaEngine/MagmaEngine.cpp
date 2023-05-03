
#include "framework.h"
#include "MagmaEngine.h"

#include <Render/render_manager.h>
#include <Render/ui_manager.h>
#include <Input/input_manager.h>
#include <Physics/physics_manager.h>
#include <Sounds/sound_manager.h>
#include <EC/scene_manager.h>
#include <EC/scene.h>
#include <Lua/scene_loader.h>
#include <EC/factory_manager.h>
#include <EC/init_factories.h>

#include "SDL_timer.h"

namespace magma_engine
{
	CMagmaEngine* CMagmaEngine::_instance = nullptr;

	// Constructor de clase exportada.
	CMagmaEngine::CMagmaEngine()
	{
	}

	RenderManager* CMagmaEngine::getRender()
	{
		return Singleton<RenderManager>::instance();;
	}

	PhysicsManager* CMagmaEngine::getPhysics()
	{
		return Singleton<PhysicsManager>::instance();;
	}

	InputManager* CMagmaEngine::getInput()
	{
		return Singleton<InputManager>::instance();;
	}

	AudioManager* CMagmaEngine::getAudio()
	{
		return Singleton<AudioManager>::instance();;
	}

	SceneManager* CMagmaEngine::getSceneMngr()
	{
		return Singleton<SceneManager>::instance();;
	}
	
	UI_Manager* CMagmaEngine::getUI()
	{
		return Singleton<UI_Manager>::instance();;
	}

	bool CMagmaEngine::loadGame()
	{
#ifdef _DEBUG
		game = LoadLibrary(TEXT("TheRiseOfSuxalote_d"));
#else 
		game = LoadLibrary(TEXT("TheRiseOfSuxalote"));
#endif 
		if (game != NULL)
		{
			std::cout << "Libreria del juego cargada" << std::endl;
			GameString gameSceneName = (GameString)GetProcAddress(game, "gameNameScene");
			gComponent = (GameComponents)GetProcAddress(game, "setUpGameFactories");

			if (gameSceneName != NULL)
				name = gameSceneName();
			else
				std::cout << "No se ha encontrado el metodo del juego\n";

			return true;
		}
		else
		{
			std::cout << "Libreria del juego no encontrada" << std::endl;
			return false;
		}
	}

	bool CMagmaEngine::Init()
	{
		if (_instance == nullptr)
		{
			_instance = new CMagmaEngine();

			// Si consigue cargar el juego, se inicializa el resto
			if (loadGame())
			{
				// RENDER
				if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false))
				{
					if (!Singleton<RenderManager>::instance()->initApp())
					{
						ShutDown(2);
						return false;
					}
				}
				else return false;

				// PHYSICS
				if (Singleton<PhysicsManager>::init())
				{
					if (!Singleton<PhysicsManager>::instance()->initPhysics())
					{
						ShutDown(1);
						return false;
					}
				}
				else return false;

				// INITS RESTANTES
				if (Singleton<UI_Manager>::init()		// ------ UI ------
					&& Singleton<InputManager>::init()	// ------ INPUT ------
					&& Singleton<SoundManager>::init()	// ------ SOUND ------
					&& Singleton<SceneManager>::init()	// ------ SCENE MANAGER ------
					&& Singleton<SceneLoader>::init()	// ------ SCENE_LOADER ------
					&& Singleton<FactoryManager>::init()
					)
				{
					Singleton<SoundManager>::instance()->initAudio();
					setUpFactories();
					
					// Cargamos los componentes del juego
					if (gComponent != NULL)
						gComponent(Singleton<FactoryManager>::instance());
					else
					{
						std::cout << "WARNING! No se cargaron los componentes del juego correctamente \n\n";
						ShutDown();
						return false;
					}
					

					// Carga de mapa
					int sceneRead = Singleton<magma_engine::SceneLoader>::instance()->loadScene(name);
					bool sceneCreated = false;
					Scene* scn = nullptr;

					if (sceneRead >= 0) {
						scn = new Scene();
						SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile();

						sceneCreated = scn->loadScene(sncMp);
						if (sceneCreated)
							Singleton<magma_engine::SceneManager>::instance()->changeScene(scn);
					}

					return true;
				}
				else {
					ShutDown();
					return false;
				}
			}

		}

		return false;
	}

	bool CMagmaEngine::ShutDown(int i)
	{
		switch (i) {
		case 0:
			// ------ SCENE_LOADER ------
			Singleton<SceneLoader>::release();
			// ------ SCENE MANAGER ------
			Singleton<SceneManager>::release();
			// ------ SOUND ------
			Singleton<SoundManager>::release();
			// ------ INPUT ------
			Singleton<InputManager>::release();
			// ------ UI ------
			Singleton<UI_Manager>::release();
		case 1:
			// ------ PHYSICS ------
			Singleton<PhysicsManager>::instance()->detachPhysics();
			Singleton<PhysicsManager>::release();
		case 2:
			// ------ RENDER ------
			Singleton<RenderManager>::instance()->closeApp();
			Singleton<RenderManager>::release();
		default:
			break;
		}

		bool success = FreeLibrary(game);

		delete _instance;

		return success;
	}

	void CMagmaEngine::run()
	{
		// ---------- BUCLE PRINCIPAL ----------
		bool error = false;

		// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
		int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
		// Cálculo del tiempo, en milisegundos, entre fotogramas
		int timeSinceLastFrame = 0;


		while (!Singleton<InputManager>::instance()->exitRequested() && !error)
		{
			// Marcas de tiempo y cálculo del "delta"
			timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
			lastFrameTime = (int)SDL_GetTicks();

			// Ver si recibimos input
			Singleton<InputManager>::instance()->inputEvent();


			// Actualizar mundo de fisicas
			Singleton<PhysicsManager>::instance()->update(timeSinceLastFrame * 0.001f);


			// Actualizar la escena y todas sus entidades
			Singleton<SceneManager>::instance()->update(timeSinceLastFrame * 0.001f);

			// Actualizamos todas las entidades de la escena y borramos las escenas en la cola de eliminacion
			Singleton<magma_engine::SceneManager>::instance()->update(timeSinceLastFrame * 0.001f);


			// Borrar elementos de pantalla y volver a dibujarlos
			//Control de cuándo se borran aquellos que deben ser borrados
			int f = Singleton<magma_engine::RenderManager>::instance()->refreshObjects();
			if (f != 0)
			{
				std::cout << f <<
					" destrucciones graficas diferidas fallidas\t/!\\" << std::endl;
			}
			if (!Singleton<RenderManager>::instance()->renderFrame())
				error = true;

			Singleton<magma_engine::UI_Manager>::instance()->update();


			// Si la ventana cambia de tamaño
			if (Singleton<InputManager>::instance()->hasWindowChange())
				Singleton<RenderManager>::instance()->notifyWindowResized();


			// Vaciamos el input
			Singleton<InputManager>::instance()->flush();
		}
		if (error)
		{
			std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
		}
	}

}

