
#include "framework.h"
#include "MagmaEngine.h"

#include <Render/render_manager.h>
#include <Render/ui_manager.h>
#include <Input/input_manager.h>
#include <Physics/physics_manager.h>
#include <Sounds/sound_manager.h>
#include <EC/scene_manager.h>
#include <Lua/scene_loader.h>

#include "SDL_timer.h"

namespace magma_engine
{
	CMagmaEngine* CMagmaEngine::_instance = nullptr;

	// Constructor de clase exportada.
	CMagmaEngine::CMagmaEngine()
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
			GameExample pruebaJuego = (GameExample)GetProcAddress(game, "prueba");


			if (pruebaJuego != NULL)
				pruebaJuego();
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
					)
				{
					Singleton<magma_engine::SoundManager>::instance()->initAudio();
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


			// Si la ventana cambia de tamaño
			if (Singleton<InputManager>::instance()->hasWindowChange())
				Singleton<RenderManager>::instance()->notifyWindowResized();


			// Borrar elementos de pantalla y volver a dibujarlos
			Singleton<RenderManager>::instance()->refreshObjects();
			if (!Singleton<RenderManager>::instance()->renderFrame())
				error = true;


			// Vaciamos el input
			Singleton<InputManager>::instance()->flush();
		}
		if (error)
		{
			std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
		}
	}
}

