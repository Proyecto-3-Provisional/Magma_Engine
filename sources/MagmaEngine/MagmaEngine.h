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
	class RenderManager;
	class InputManager;
	class PhysicsManager;
	class SoundManager;
	class SceneManager;
	class UI_Manager;


	class FactoryManager;

	class MAGMAENGINE_API CMagmaEngine {
	public:
		bool Init();
		bool ShutDown(int i = 0);
		void run();
		static CMagmaEngine* _instance;
		CMagmaEngine();

		// Get Instances
		RenderManager* getRender();
		InputManager* getInput();
		PhysicsManager* getPhysics();
		SoundManager* getAudio();
		SceneManager* getSceneMngr();
		UI_Manager* getUI();

	private:
		typedef void(__cdecl* GameComponents)(FactoryManager*); // Añade las factorías del juego
		typedef std::string(*GameString)(); // Devuelve el mapa a cargar
		typedef void(__cdecl* EngineReference)(CMagmaEngine*); // Envía referencia al motor

		HMODULE game;
		bool loadGame();
		GameComponents gComponent;
		std::string name;
		EngineReference eReference;
	};

	//extern MAGMAENGINE_API int nMagmaEngine;

	//MAGMAENGINE_API int fnMagmaEngine(void);
}


