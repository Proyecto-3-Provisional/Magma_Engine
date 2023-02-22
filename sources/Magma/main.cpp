#include <iostream>

#include "Render/App.h" // GUILLERMO: "...proyectos como espacios de nombres"

#include "SDL_timer.h"	// para calcular el tiempo transcurrido entre fotogramas

#include "OgreRoot.h" // ¡!

#include "entity_manager.h"
#include "entity.h"
#include "transform.h"

//#include "Input/input_manager.h"

int mainCode() {
	std::cout << "======== MAGMA iniciado ========\n";

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS

	EntityManager* manager_ = new EntityManager();
	auto e_ = manager_->addEntity();
	e_->addComponent<Transform>();
	
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS CONTINUA EN EL WHILE

	float lastFrameTime = SDL_GetTicks(); // Milisegundos transcurridos desde el inicio
	float timeSinceLastFrame = 0;
	
	App app;
	bool correct = app.initApp(); // Inicio
	if (!correct) {
		app.closeApp(); // Fin
		return 1;
	}
	while (!app.salir) {
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime; // Milisegundos transcurridos desde el inicio
		lastFrameTime = SDL_GetTicks();

		// Renderizar fotogramas de uno en uno, ya veremos si se quieren más...
		app.getRoot()->renderOneFrame(); // startRendering
		app.rotate(timeSinceLastFrame); // Rotar cubo para ver cambios entre fotogramas


		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS
		
		manager_->update();
		////sdlutils().clearRenderer();
		//manager_->render();
		////sdlutils().presentRenderer();
		//manager_->refresh();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS

	}
	app.closeApp(); // Fin

	return 0;
}

// Diferentes funciones como punto de entrada por defecto al seleccionar
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
