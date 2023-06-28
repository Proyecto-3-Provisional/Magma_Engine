#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <string>
#include <vector>
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
		// Añade las factorías del juego
		typedef void(__cdecl* GameComponents)(); 
		// Devuelve el mapa a cargar
		typedef void(__cdecl* GameString)(std::vector<std::string>&);

		HMODULE game;
		bool loadGame();
		GameComponents gComponent;
		std::vector<std::string> names;
	};

	//extern MAGMAENGINE_API int nMagmaEngine;

	//MAGMAENGINE_API int fnMagmaEngine(void);
}


