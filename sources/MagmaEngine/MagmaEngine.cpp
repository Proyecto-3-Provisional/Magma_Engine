#include "pch.h"
#include "framework.h"
#include "MagmaEngine.h"



CMagmaEngine* CMagmaEngine::_instance = nullptr;

// Ejemplo de variable exportada
MAGMAENGINE_API int nMagmaEngine=0;

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
	Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false);
	if (_instance == nullptr)
	{
		_instance = new CMagmaEngine();

		// Aqui deberiamos de meter las instancias de todos los proyectos

		if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false) // ------ RENDER ------
			&& Singleton<ec::EntityManager>::init()									// ------ EC ------
			&& Singleton<PhysicsManager>::init() 									// ------ PHYSICS ------
			&& Singleton<UI_Manager>::init()										// ------ UI ------
			&& Singleton<InputManager>::init()										// ------ INPUT ------
			&& Singleton<SoundManager>::init()										// ------ SOUND ------
			)
		{


			if (!Singleton<RenderManager>::instance()->initApp() || !Singleton<PhysicsManager>::instance()->initPhysics()) // if (!correct)
			{
				// Fin del renderizado
				Singleton<RenderManager>::instance()->closeApp();
				Singleton<RenderManager>::instance()->release();

				Singleton<PhysicsManager>::instance()->detachPhysics();

				return false;
			}
			}
			else
			{
				return false;
			}

			// Error en la asignacion de los static
			//render = Singleton<RenderManager>::instance();
			//ui = Singleton<UI_Manager>::instance();
			//physics = Singleton<PhysicsManager>::instance();
			//input = Singleton<InputManager>::instance();
			//audio = Singleton<SoundManager>::instance();
			//ec = Singleton<ec::EntityManager>::instance();

			return true;
	}

    return false;
}

bool CMagmaEngine::ShutDown()
{
	// ------ EC ------
	Singleton<ec::EntityManager>::release();

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

    return true;
}

void CMagmaEngine::run()
{

}

