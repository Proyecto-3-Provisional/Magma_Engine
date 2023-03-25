#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif


class RenderManager;
class UIManager;
class PhysicsManager;
class AudioManager;
class InputManager;
class EC;


class MAGMAENGINE_API CMagmaEngine {
public:
	static bool Init();
	static bool ShutDown();
	void run();
	// static bool setup(); // Se podria hacer en el propio Init
	
	static CMagmaEngine* _instance;
	CMagmaEngine(void);
private:
	/*RenderManager* render;
	UIManager* ui;
	PhysicsManager* physics;
	AudioManager* audio;
	InputManager* input;
	EC* ec;*/
};

extern MAGMAENGINE_API int nMagmaEngine;

MAGMAENGINE_API int fnMagmaEngine(void);
