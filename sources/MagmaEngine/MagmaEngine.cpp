#include "pch.h"
#include "framework.h"
#include "MagmaEngine.h"
#include "SDL_timer.h"



CMagmaEngine* CMagmaEngine::_instance = nullptr;

// Ejemplo de variable exportada
MAGMAENGINE_API int nMagmaEngine = 0;

// Ejemplo de función exportada.
MAGMAENGINE_API int fnMagmaEngine(void)
{
	return 0;
}

// Constructor de clase exportada.
CMagmaEngine::CMagmaEngine()
{
	return;
}

bool CMagmaEngine::Init()
{
	if (_instance == nullptr)
	{
		_instance = new CMagmaEngine();

		// RENDER
		if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false))
		{
			if (!Singleton<RenderManager>::instance()->initApp())
			{
				// Fin del renderizado
				Singleton<RenderManager>::instance()->closeApp();
				Singleton<RenderManager>::instance()->release();
				return false;
			}
		}
		else return false;

		// PHYSICS
		if (Singleton<PhysicsManager>::init())
		{
			if (!Singleton<PhysicsManager>::instance()->initPhysics()) 
			{
				// Fin del renderizado
				Singleton<RenderManager>::instance()->closeApp();
				Singleton<RenderManager>::instance()->release();

				// Cerrar el mundo fisico
				Singleton<PhysicsManager>::instance()->detachPhysics();
				return false;
			}
		}
		else return false;

		// INITS RESTANTES
		if (Singleton<UI_Manager>::init()										// ------ UI ------
			&& Singleton<InputManager>::init()										// ------ INPUT ------
			&& Singleton<SoundManager>::init()										// ------ SOUND ------
			&& Singleton<SceneManager>::init()										// ------ SCENE MANAGER ------
			)
		{
			return true;
		}
	}

	return false;
}

bool CMagmaEngine::ShutDown()
{
	// ------ SCENE MANAGER ------
	Singleton<SceneManager>::release();

	// ------ PHYSICS ------
	Singleton<PhysicsManager>::instance()->detachPhysics();
	Singleton<PhysicsManager>::release();

	// ------ INPUT ------
	Singleton<InputManager>::release();

	// ------ UI ------
	Singleton<UI_Manager>::release();

	// ------ RENDER ------
	Singleton<RenderManager>::instance()->closeApp();
	Singleton<RenderManager>::release();

	// ------ SOUND ------
	Singleton<SoundManager>::release();

	delete _instance;

	return true;
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
		Singleton<PhysicsManager>::instance()->update(timeSinceLastFrame);


		// Actualizar la escena y todas sus entidades
		Singleton<SceneManager>::instance()->update(timeSinceLastFrame);


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

