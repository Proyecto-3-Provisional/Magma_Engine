#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif


#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Input/input_manager.h"
#include "Physics/physics_manager.h"
#include "Sounds/sound_manager.h"
#include "EC/entity_manager.h"

//class RenderManager;
//class UI_Manager;
//class PhysicsManager;
//class InputManager;
//class SoundManager;
//class ec::EntityManager;

class MAGMAENGINE_API CMagmaEngine {
public:
	static bool Init();
	static bool ShutDown();
	void run();
	// static bool setup(); // Se podria hacer en el propio Init
	
	static CMagmaEngine* _instance;
	CMagmaEngine(void);
private:
	static RenderManager* render;
	static UI_Manager* ui;
	static PhysicsManager* physics;
	static SoundManager* audio;
	static InputManager* input;
	static ec::EntityManager* ec;
};

extern MAGMAENGINE_API int nMagmaEngine;

MAGMAENGINE_API int fnMagmaEngine(void);
