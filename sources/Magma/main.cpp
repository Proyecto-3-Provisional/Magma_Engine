// Fugas Memoria
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>

// para calcular el tiempo transcurrido entre fotogramas
#include <SDL_timer.h>

// GUILLERMO: "...proyectos como espacios de nombres"
#include <Render/render_manager.h>
#include <Render/ui_manager.h>
#include <Render/ui_button.h>
#include <Render/mesh.h>	
#include <Input/input_manager.h>
#include <Physics/physics_manager.h>
#include <Physics/rigidbody.h>
#include <Sounds/sound_manager.h>
#include <EC/entity_manager.h>
#include <EC/entity.h>
#include <EC/vector3D.h>
#include <EC/fps_counter.h>
#include <EC/transform.h>
#include <Render/image.h>
#include <Render/text.h>
#include <Render/button.h>
#include <Sounds/audio_source.h>
#include <EC/factory_manager.h>
#include <EC/init_factories.h>
#include <Lua/scene_loader.h>
#include <EC/scene.h>
#include <EC/scene_manager.h>

// DECLARACIÓN DE FUNCIONES
void initManagers();
void releaseManagers();

int mainCode() {
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//
#ifdef _DEBUG

#if 1 // por comodidad (0 -> false; No 0 -> true)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else	
	_CrtSetBreakAlloc(12944); // id del new que queremos borrar
#endif
#endif
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//

	// Temporizador debug (también para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;


	// ---------- Inicialización MANAGERS ----------
	initManagers();
	std::cout << "Managers inicializados\n";


	// ---------- Inicialización RENDER ----------

	// Carga de mapa
	int sceneRead = Singleton<magma_engine::SceneLoader>::instance()->loadScene("assets/scenes/test.magmascene");
	bool sceneCreated = false;
	magma_engine::Scene* scn = nullptr;
	if (sceneRead >= 0) {
		SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile();

		scn = new magma_engine::Scene();
		sceneCreated = scn->loadScene(sncMp);
		if (sceneCreated)
			Singleton<magma_engine::SceneManager>::instance()->changeScene(scn);
	}

	// ---------- BUCLE PRINCIPAL ----------
	bool error = false;
	int s = 50;

	if (sceneCreated) 
	{
		while (!Singleton<magma_engine::InputManager>::instance()->exitRequested() && !error && s > 0)
		{
			// Marcas de tiempo y cálculo del "delta"
			timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
			lastFrameTime = (int)SDL_GetTicks();

			// ------- TEST RENDER -------

			//Prueba de animaciones
			Singleton<magma_engine::RenderManager>::instance()->stepAnimations(timeSinceLastFrame);
			//Imprimir número de objetos gráficos cada cierto tiempo
			miliecsSinceLastReport += timeSinceLastFrame;
			/*if (miliecsSinceLastReport > miliecsToReport)
			{
				std::cout << "Objetos gráficos: " <<
					Singleton<magma_engine::RenderManager>::instance()->getNumObjects() << std::endl;
			}*/
			//Control de cuándo se borran aquellos que deben ser borrados
			int f = Singleton<magma_engine::RenderManager>::instance()->refreshObjects();
			if (f != 0)
			{
				std::cout << f <<
					" destrucciones graficas diferidas fallidas\t/!\\" << std::endl;
			}

			//Renderizar fotogramas de uno en uno
			if (!Singleton<magma_engine::RenderManager>::instance()->renderFrame())
				error = true;


			// ------- TEST INPUT & UI -------
			Singleton<magma_engine::InputManager>::instance()->inputEvent();

			// ------- TEST EC -------
			Singleton<magma_engine::SceneManager>::instance()->update(timeSinceLastFrame * 0.001f);
			Singleton<magma_engine::PhysicsManager>::instance()->update(timeSinceLastFrame * 0.001f);

			//Redimensión ventana
			if (Singleton<magma_engine::InputManager>::instance()->hasWindowChange()) {
				Singleton<magma_engine::RenderManager>::instance()->notifyWindowResized();
			}

		}
		if (error)
		{
			std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
		}
	}


	// Carga de mapa
	if (sceneRead >= 0) 
	{
		if (sceneCreated)
			Singleton<magma_engine::SceneManager>::instance()->popScene();
		delete scn;
		scn = nullptr;
	}

	releaseManagers();

	return 0;
}

void initManagers() {
	// ------ RENDER		------
	if (Singleton<magma_engine::RenderManager>::init(false, 1280, 720, false, true, 4, false))
	{
		if (!Singleton<magma_engine::RenderManager>::instance()->initApp()) // if (!correct)
		{
			// Fin del renderizado
			Singleton<magma_engine::RenderManager>::instance()->closeApp();
			Singleton<magma_engine::RenderManager>::instance()->release();
		}
	}
	// ------ FACTORY		------
	Singleton<magma_engine::FactoryManager>::init();
	magma_engine::setUpFactories();
	// ------ GAME SCENES	------
	Singleton<magma_engine::SceneManager>::init();
	// ------ LUA SCENES	------
	Singleton<magma_engine::SceneLoader>::init();

	// ------ PHYSICS		------
	bool correct = false;
	if (Singleton<magma_engine::PhysicsManager>::init())
		correct = Singleton<magma_engine::PhysicsManager>::instance()->initPhysics();
	if (!correct)
		// Fin del renderizado
		Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	/// esta detección con 'correct' HAY QUE HACERLA PARA TODO !!!!
	// ------ UI			------
	Singleton<magma_engine::UI_Manager>::init();
	// ------ INPUT			------
	Singleton<magma_engine::InputManager>::init();
	// ------ SOUND			------
	if (Singleton<magma_engine::SoundManager>::init())
		Singleton<magma_engine::SoundManager>::instance()->initAudio();
}

void releaseManagers() {
	// ------ LUA SCENES	------
	Singleton<magma_engine::SceneLoader>::release();
	// ------ GAME SCENES	------
	Singleton<magma_engine::SceneManager>::release();
	// ------ PHYSICS		------
	Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	Singleton<magma_engine::PhysicsManager>::release();
	// ------ INPUT			------
	Singleton<magma_engine::InputManager>::release();
	// ------ UI			------
	Singleton<magma_engine::UI_Manager>::release();
	// ------ RENDER		------
	Singleton<magma_engine::RenderManager>::instance()->closeApp();
	Singleton<magma_engine::RenderManager>::release();
	// ------ SOUND			------
	Singleton<magma_engine::SoundManager>::release();
	// ------ FACTORY		------
	Singleton<magma_engine::FactoryManager>::release();
}

// Esta disyuntiva hace que en config. Release no aparezca la consola
// Hay diferentes funciones como punto de entrada por defecto al seleccionar
// valores distintos en 'Vinculador > Sistema > Subsistema' según la Configuración
#if _DEBUG
int main(int argc, char const** argv) {
	return mainCode();
}
#else
int __stdcall WinMain(void*, void*, char* cmdLine, int) {
	return mainCode();
}
#endif
