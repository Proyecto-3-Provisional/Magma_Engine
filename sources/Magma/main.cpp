#include <iostream>

#include "SDL_timer.h"	// para calcular el tiempo transcurrido entre fotogramas

// GUILLERMO: "...proyectos como espacios de nombres"
#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Input/input_manager.h"

#include "entity_manager.h"
#include "entity.h"
#include "transform.h"

/////
//===
/////
// Control de la velocidad de rotación
const float rotationVelocity = 0.05;
// Temporizador debug
const int miliecsToReport = 2000;
int miliecsSinceLastReport = 0;
// Temporizador ejemplo cubo
const int miliecsToDisappear = 8000;
int milisecsAcc = 0;
bool cubeDisappearance = false;
/////
//===
/////

int mainCode() {
	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	float lastFrameTime = SDL_GetTicks();
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	float timeSinceLastFrame = 0;

	// Inicio del renderizado
	RenderManager renderMngr;
	bool correct = renderMngr.initApp();

	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS
	ecs::EntityManager* entityManager = new ecs::EntityManager();
	auto e_ = entityManager->addEntity();
	Transform* tr_ = e_->addComponent<Transform>();
	//e_->addComponent();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS CONTINUA EN EL WHILE

	if (!correct)
	{
		// Fin del renderizado
		renderMngr.closeApp();
		return 1;
	}

	//******************************************************
	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	UI_Manager* ui = new UI_Manager();
	ui->createText("Prueba", 0, 0, 200, 34, "Arial", "Who's the impostor?", 0.5,0.3,0.1);
	//******************************************************

	//******************************************************
	InputManager* input = new InputManager; 

	bool error = false;
	while (!renderMngr.exitRequested() && !error)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = SDL_GetTicks();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
		input->inputEvent(); 

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS
		entityManager->update();
		//manager_->removeComponent<Transform>(e_);
		////sdlutils().clearRenderer();
		//manager_->render();
		////sdlutils().presentRenderer();
		entityManager->refresh();
		//entityManager->removeComponent<Transform>(e_);
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS

		// Ejemplo de borrado de objeto -> se efectuará en 'refresh'
		milisecsAcc += timeSinceLastFrame;
		if (!cubeDisappearance && milisecsAcc > miliecsToDisappear) {
			bool r1, r2;
			r1 = renderMngr.sunsetObject("cube");
			r2 = renderMngr.sunsetObject("cube_empty");
			if (r1 && r2) cubeDisappearance = true;
		}
		
		// Ejemplo de movimiento: rotar objetos para ver cambios entre fotogramas
		GraphicalObject* ajolote = renderMngr.getObject("suxalote");
		if (ajolote)
			ajolote->yaw(rotationVelocity * timeSinceLastFrame);
		GraphicalObject* ficticioTripulacion = renderMngr.getObject("crew");
		if (ficticioTripulacion)
			ficticioTripulacion->roll(-rotationVelocity * timeSinceLastFrame);
		GraphicalObject* ficticioCubo = renderMngr.getObject("cube_empty");
		if (ficticioCubo)
			ficticioCubo->pitch(rotationVelocity * timeSinceLastFrame);

		// Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport) {
			std::cout << "GObjects: " << renderMngr.getNumObjects() << std::endl;
			std::cout << "GObjects sunset: " << renderMngr.getNumObjectsToRemove() << std::endl;
			miliecsSinceLastReport = 0;
		}

		// Control de cuándo se borran aquellos que deben ser borrados
		/*bool b = */renderMngr.refreshObjects();

		// Renderizar fotogramas de uno en uno, ya veremos si se quieren más...
		if (!renderMngr.renderFrame())
			error = true;
	}
	if (error)
	{
		std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
	}

	delete ui; ui = nullptr;
	delete entityManager; entityManager = nullptr;

	// Fin del renderizado
	renderMngr.closeApp();

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
