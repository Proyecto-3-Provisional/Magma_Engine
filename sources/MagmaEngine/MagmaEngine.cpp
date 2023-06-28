
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
	CMagmaEngine::CMagmaEngine() : gComponent(NULL), game(NULL)
	{
	}

	CMagmaEngine::~CMagmaEngine()
	{

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
				gameSceneName(names);
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
			_instance = this;

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
				// ------ UI ------
				if (Singleton<UI_Manager>::init()
					// ------ INPUT ------
					&& Singleton<InputManager>::init()
					// ------ SOUND ------
					&& Singleton<SoundManager>::init()
					// ------ SCENE MANAGER ------
					&& Singleton<SceneManager>::init()
					// ------ SCENE_LOADER ------
					&& Singleton<SceneLoader>::init()
					// ------ FACTORY MANAGER ------
					&& Singleton<FactoryManager>::init()
					)
				{
					Singleton<SoundManager>::instance()->initAudio();
					setUpFactories();

					// Cargamos los componentes del juego
					if (gComponent != NULL)
						gComponent();
					else
					{
						std::cout << "WARNING! No se cargaron los componentes del juego correctamente \n\n";
						ShutDown();
						return false;
					}


					// Carga de mapa
					bool todoCargado = true;
					for (std::string name : names) {
						int sceneRead = Singleton<magma_engine::SceneLoader>::instance()->loadScene(name);

						if (sceneRead < 0) {
							Singleton<magma_engine::RenderManager>::instance()->makeMessageBox("LUA", ("La escena " + name + " no se ha podido leer con exito").c_str());
							ShutDown();
							return false;
						}
					}
					Scene* scn = new Scene();
					SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile(names[0]);

					if (scn->loadScene(sncMp)) {
						Singleton<magma_engine::SceneManager>::instance()->changeScene(scn);
						return true;
					}
					else {
						Singleton<magma_engine::RenderManager>::instance()->makeMessageBox("LUA", ("La escena " + names[0] + " no se ha podido cargar con exito").c_str());
						delete scn;
					}
				}
				ShutDown();
			}

		}

		return false;
	}

	bool CMagmaEngine::ShutDown(int i)
	{
		switch (i) {
		case 0:
			// ------ FACTORY MANAGER ------
			Singleton<FactoryManager>::release();
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


		return success;
	}

	void CMagmaEngine::run()
	{
		// ---------- BUCLE PRINCIPAL ----------
		bool error = false;

		// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
		// uint32 a int
		int lastFrameTime = (int)SDL_GetTicks();
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
			if (Singleton<SceneManager>::instance()->isSceneFailed())
				error = true;


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

