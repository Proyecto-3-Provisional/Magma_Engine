#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <string>

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
		//typedef void(__cdecl* GameString)(std::string);
		typedef std::string(*GameString)();

		HMODULE game;
		bool loadGame();
		
		std::string name;
	};

	//extern MAGMAENGINE_API int nMagmaEngine;

	//MAGMAENGINE_API int fnMagmaEngine(void);
}


