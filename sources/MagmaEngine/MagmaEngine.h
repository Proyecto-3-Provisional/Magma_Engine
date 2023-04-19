#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif


#include <Render/render_manager.h>
#include <Render/ui_manager.h>
#include <Input/input_manager.h>
#include <Physics/physics_manager.h>
#include <Sounds/sound_manager.h>
#include <EC/scene_manager.h>


class MAGMAENGINE_API CMagmaEngine {
public:
	bool Init();
	bool ShutDown();
	void run();
	static CMagmaEngine* _instance;
	CMagmaEngine();
private:
	typedef void(__cdecl* GameExample)(void);
	
	HMODULE game;
	bool loadGame();
};

//extern MAGMAENGINE_API int nMagmaEngine;

//MAGMAENGINE_API int fnMagmaEngine(void);
