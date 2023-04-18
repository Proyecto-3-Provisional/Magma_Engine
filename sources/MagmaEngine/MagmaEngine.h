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
#include "EC/scene_manager.h"


class MAGMAENGINE_API CMagmaEngine {
public:
	static bool Init();
	static bool ShutDown();
	void run();
	
	static CMagmaEngine* _instance;
	CMagmaEngine();
};

//extern MAGMAENGINE_API int nMagmaEngine;

//MAGMAENGINE_API int fnMagmaEngine(void);
