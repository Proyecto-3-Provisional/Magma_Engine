#include <iostream>

// para calcular el tiempo transcurrido entre fotogramas
#include "SDL_timer.h"

// GUILLERMO: "...proyectos como espacios de nombres"
#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Render/UI_Text.h"
#include "Render/UI_Image.h"
#include "Input/input_manager.h"
#include "Physics/physics_manager.h"
#include "Sounds/sound_manager.h"

#include "ECS/entity_manager.h"
#include "ECS/entity.h"
#include "ECS/test_axl_mov.h"
#include "ECS/vector3D.h"

//DECLARACIONES DE FUNCIONES
void ecTestInit(ec::EntityManager* em, RenderManager* rm);
void ecTestUpdate(ec::EntityManager* em);

int mainCode() {
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
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	float lastFrameTime = SDL_GetTicks();
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	float timeSinceLastFrame = 0;

	//_RENDER_ Inicio del renderizado
	RenderManager* renderMngr = new RenderManager(false);
	bool correct = renderMngr->initApp();

	//>>>>>>>>>>>>>>>>>>>>>>> TEST EC
	ec::EntityManager* entityManager = new ec::EntityManager();
	ecTestInit(entityManager, renderMngr);
	//>>>>>>>>>>>>>>>>>>>>>>> TEST EC CONTINUA EN EL WHILE

	//_RENDER_
	if (!correct)
	{
		// Fin del renderizado
		renderMngr->closeApp();
		return 1;
	}

	//*************************************
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

	//>>>>>>>>>>>>>>>>>>>>>>> TEST UI MANAGER
	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	UI_Manager* ui = new UI_Manager();
	
	UI_Text* testText = ui->createElement<UI_Text>("Prueba", 0, 0, 200, 34, "Arial", "Who's the impostor?", 0.5, 0.3, 0.1);
	testText->setText("Ahhh yessss");

	UI_Image* testImage = ui->createElement<UI_Image>("ImgPrueba", "golf", 0, 80, 100, 100);
	//testImage->changeImage("ImgPruebaImage", "rat");
	//>>>>>>>>>>>>>>>>>>>>>>>

	// _INPUT_
	InputManager* input = new InputManager;

	//>>>>>>>>>>>>>>>>>>>>>>> TEST SOUND MANAGER
	SoundManager* soundManager = new SoundManager();
	soundManager->playSound();

	renderMngr->setBgColor(0.8, 0.8, 0.7);
	renderMngr->objectShowMode(0);

	//_RENDER_ Cacheo de objetos gráficos
	GraphicalObject* ajolote = renderMngr->getObject("suxalote");
	GraphicalObject* ficticioTripulacion = renderMngr->getObject("crew");
	GraphicalObject* tripulante_amarillo = renderMngr->getObject("crewmate_amongus_yellow");
	ficticioCubo = renderMngr->getObject("cube_empty");

	// Bucle Principal del Motor //
	bool error = false;
	int s = 50;
	while (!input->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = SDL_GetTicks();

		//>>>>>>>>>>>>>>>>>>>>>>> TEST PHYSICS
		physMngr->update();
		// Para ver los couts de colisiones descomentar la s
		// s--;

		//>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
		input->inputEvent();

		//>>>>>>>>>>>>>>>>>>>>>>> TEST EC
		ecTestUpdate(entityManager);

		//_RENDER_ Ejemplo de borrado de objeto -> se efectuará en 'refresh'
		milisecsAcc += timeSinceLastFrame;
		if (!cubeDisappearance && milisecsAcc > miliecsToDisappear) {
			bool r1, r2;
			r1 = renderMngr->sunsetObject("cube");
			r2 = renderMngr->sunsetObject("cube_empty");
			if (r1 && r2)
			{
				cubeDisappearance = true;
				ficticioCubo = nullptr;
			}
		}

		//_RENDER_ Ejemplo de movimiento: rotar objetos para ver cambios entre fotogramas
		ajolote->yaw(rotationVelocity * timeSinceLastFrame);
		ficticioTripulacion->roll(-rotationVelocity * timeSinceLastFrame);
		tripulante_amarillo->yaw(rotationVelocity * timeSinceLastFrame);
		if (ficticioCubo)
			ficticioCubo->pitch(rotationVelocity * timeSinceLastFrame);

		//_RENDER_ Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport) {
			std::cout << "Objetos gráficos: "
				<< renderMngr->getNumObjects() << std::endl;
			miliecsSinceLastReport = 0;
		}

		//_RENDER_ Control de cuándo se borran aquellos que deben ser borrados
		int f = renderMngr->refreshObjects();
		if (f != 0)
		{
			std::cout << f <<
				"destrucciones gráficas diferidas fallidas\t/!\\" << std::endl;
		}

		//_RENDER_ Renderizar fotogramas de uno en uno, ya veremos si se quieren más...
		if (!renderMngr->renderFrame())
			error = true;
	}
	if (error)
	{
		std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
	}

	delete soundManager; soundManager = nullptr;
	delete input; input = nullptr;
	delete ui; ui = nullptr;
	delete physMngr; physMngr = nullptr;
	delete entityManager; entityManager = nullptr;
	// Fin del renderizado
	renderMngr->closeApp();
	delete renderMngr; renderMngr = nullptr;

	return 0;
}

void ecTestInit(ec::EntityManager* entityManager, RenderManager* renderMngr) {
	GraphicalObject* jo = renderMngr->addObject("uxalote", nullptr, "axolotl.mesh", "axolotl");
	jo->setPosition({ 0, 0, 50 });
	jo->setScale({ 40, 40, 40 });

	auto e_ = entityManager->addEntity(jo);
	TestAxlMov* tr_ = e_->addComponent<TestAxlMov >(Vector3D(), Vector3D(10, 10, 10));
}
void ecTestUpdate(ec::EntityManager* entityManager) {
	entityManager->update();
	entityManager->refresh();
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
