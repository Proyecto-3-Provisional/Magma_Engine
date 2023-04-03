#include "pch.h"
#include "framework.h"
#include "MagmaEngine.h"

#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Input/input_manager.h"
#include "Physics/physics_manager.h"
#include "Sounds/sound_manager.h"
#include "EC/entity_manager.h"


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
	if (_instance == nullptr)
	{
		_instance = new CMagmaEngine();

		// Aqui deberiamos de meter las instancias de todos los proyectos

		//if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false) // ------ RENDER ------
		//	&& Singleton<ec::EntityManager>::init()									// ------ EC ------
		//	&& Singleton<PhysicsManager>::init() 									// ------ PHYSICS ------
		//	&& Singleton<UI_Manager>::init()										// ------ UI ------
		//	&& Singleton<InputManager>::init()										// ------ INPUT ------
		//	&& Singleton<SoundManager>::init()										// ------ SOUND ------
		//	)
		//{


		//	if (!Singleton<RenderManager>::instance()->initApp() || !Singleton<PhysicsManager>::instance()->initPhysics()) // if (!correct)
		//	{
		//		// Fin del renderizado
		//		Singleton<RenderManager>::instance()->closeApp();
		//		Singleton<RenderManager>::instance()->release();

		//		Singleton<PhysicsManager>::instance()->detachPhysics();

		//		return false;
		//	}
		//}
		//else
		//{
		//	return false;
		//}

		return true;
	}

    return false;
}

bool CMagmaEngine::ShutDown()
{
	//// ------ EC ------
	//Singleton<ec::EntityManager>::release();

	//// ------ PHYSICS ------
	//Singleton<PhysicsManager>::instance()->detachPhysics();
	//Singleton<PhysicsManager>::release();

	//// ------ INPUT ------
	//Singleton<InputManager>::release();

	//// ------ UI ------
	//Singleton<UI_Manager>::release();

	//// ------ RENDER ------
	//Singleton<RenderManager>::instance()->closeApp();
	//Singleton<RenderManager>::release();

	//// ------ SOUND ------
	//Singleton<SoundManager>::release();

    return true;
}

void CMagmaEngine::run()
{

}

