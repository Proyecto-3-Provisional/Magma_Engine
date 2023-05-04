#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <windows.h>



namespace magma_engine
{
	class MAGMAENGINE_API CMagmaEngine {
	public:
		bool Init();
		bool ShutDown(int i = 0);
		void run();
		static CMagmaEngine* _instance;
		CMagmaEngine();
		~CMagmaEngine();

	private:
		typedef void(__cdecl* GameComponents)(); // Añade las factorías del juego
		typedef std::string(*GameString)(); // Devuelve el mapa a cargar

		HMODULE game;
		bool loadGame();
		GameComponents gComponent;
		std::string name;
	};

	//extern MAGMAENGINE_API int nMagmaEngine;

	//MAGMAENGINE_API int fnMagmaEngine(void);
}


