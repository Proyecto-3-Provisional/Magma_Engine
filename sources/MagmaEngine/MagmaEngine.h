#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif



namespace magma_engine
{
	class MAGMAENGINE_API CMagmaEngine {
	public:
		bool Init();
		bool ShutDown(int i = 0);
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
}


