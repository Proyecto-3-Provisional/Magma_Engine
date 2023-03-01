#include <iostream>

#include "SDL_timer.h"	// para calcular el tiempo transcurrido entre fotogramas

// GUILLERMO: "...proyectos como espacios de nombres"
#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Render/UI_Text.h"
#include "Render/UI_Image.h"
#include "Input/input_manager.h"
#include "Physics/physics_manager.h"

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
// Cacheo cubo
GraphicalObject* ficticioCubo = nullptr;
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
	GraphicalObject* jo = renderMngr.addObject("uxalote", nullptr, "axolotl.mesh", "axolotl");
	jo->showDebugBox(true);
	jo->setPosition({ 0, 0, 50 }); // me lo acerco a la cara 50 ud.
	jo->setScale({ 40, 40, 40 });

	ecs::EntityManager* entityManager = new ecs::EntityManager();
	auto e_ = entityManager->addEntity(jo);
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
	// PhysicsManager
	PhysicsManager* physMngr = new PhysicsManager();
	physMngr->initPhysics();
	btRigidBody* e = physMngr->addRigidBody(1, 1, 1, 10, 0, 0);
	btRigidBody* e2 = physMngr->addRigidBody(1, 1, 1, -10, 0, 0);
	btRigidBody* e3 = physMngr->addRigidBody(1, 1, 1, 0, 10, 0);
	btRigidBody* e4 = physMngr->addRigidBody(1, 1, 1, 0, -10, 0);
	e->applyCentralForce(btVector3(-1000, 0, 0));
	e2->applyCentralForce(btVector3(1000, 0, 0));
	e3->applyCentralForce(btVector3(0, -1000, 0));
	e4->applyCentralForce(btVector3(0, 1000, 0));


	//						UI MANAGER
	//******************************************************
	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	UI_Manager* ui = new UI_Manager();
	
	UI_Text* testText = ui->createElement<UI_Text>("Prueba", 0, 0, 200, 34, "Arial", "Who's the impostor?", 0.5, 0.3, 0.1);
	testText->setText("Ahhh yessss");

	UI_Image* testImage = ui->createElement<UI_Image>("ImgPrueba", "golf", 0, 80, 100, 100);
	//testImage->changeImage("golf");

	//******************************************************

	InputManager* input = new InputManager;

	renderMngr.setBgColor(0.8, 0.8, 0.7);
	renderMngr.objectShowMode(0);

	// Cacheo de objetos gráficos
	GraphicalObject* ajolote = renderMngr.getObject("suxalote");
	GraphicalObject* ficticioTripulacion = renderMngr.getObject("crew");
	ficticioCubo = renderMngr.getObject("cube_empty");
	// Cacheo de objetos gráficos

	bool error = false;
	int s = 50;
	while (!input->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = SDL_GetTicks();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST PHYSICS
		physMngr->update();
		// Para ver los couts de colisiones descomentar la s
		// s--;

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
		input->inputEvent();

		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS
		entityManager->update();

		entityManager->refresh();
		//entityManager->removeComponent<Transform>(e_);
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TEST ECS

		// Ejemplo de borrado de objeto -> se efectuará en 'refresh'
		milisecsAcc += timeSinceLastFrame;
		if (!cubeDisappearance && milisecsAcc > miliecsToDisappear) {
			bool r1, r2;
			r1 = renderMngr.sunsetObject("cube");
			r2 = renderMngr.sunsetObject("cube_empty");
			if (r1 && r2)
			{
				cubeDisappearance = true;
				ficticioCubo = nullptr;
			}
		}

		// Ejemplo de movimiento: rotar objetos para ver cambios entre fotogramas
		ajolote->yaw(rotationVelocity * timeSinceLastFrame);
		ficticioTripulacion->roll(-rotationVelocity * timeSinceLastFrame);
		if (ficticioCubo)
			ficticioCubo->pitch(rotationVelocity * timeSinceLastFrame);

		// Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport) {
			std::cout << "Objetos gráficos: " << renderMngr.getNumObjects() << std::endl;
			miliecsSinceLastReport = 0;
		}

		// Control de cuándo se borran aquellos que deben ser borrados
		int f = renderMngr.refreshObjects();
		if (f != 0)
		{
			std::cout << f << "destrucciones diferidas fallidas\t/!\\" << std::endl;
		}

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
