// Fugas Memoria
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>

// para calcular el tiempo transcurrido entre fotogramas
#include "SDL_timer.h"

// GUILLERMO: "...proyectos como espacios de nombres"
#include "Render/render_manager.h"
#include "Render/UI_Manager.h"
#include "Render/UI_Text.h"
#include "Render/UI_Image.h"
#include "Render/ui_button.h"
#include "Render/mesh.h"		//
#include "Input/input_manager.h"
#include "Physics/physics_manager.h"
#include "Sounds/sound_manager.h"
#include "ECS/entity_manager.h"
#include "ECS/entity.h"
#include "ECS/test_axl_mov.h"
#include "ECS/vector3D.h"
#include "ECS/fps_counter.h"

#define AXO_POV 0

//DECLARACIONES DE FUNCIONES
void ecTestInit(ec::EntityManager* em, ec::Entity*);
void ecTestUpdate(ec::EntityManager* em, float deltaTime);

int mainCode() {
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//
#ifdef _DEBUG

#if 1 // por comodidad (0 -> false; No 0 -> true)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else	
	_CrtSetBreakAlloc(39266); // id del new que queremos borrar
#endif
#endif
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//

	// Control de la velocidad de rotación
	const float rotationVelocity = 0.05f;
	// Temporizador debug (tb para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	// Temporizador ejemplo cubo
	const int miliecsToDisappear = 15000;
	int milisecsAcc = 0;
	bool cubeDisappearance = false;
	// Cacheo cubo
	GraphicalObject* ficticioCubo = nullptr;
	//////
	ec::Entity* sampleEntity = nullptr;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;

	//>>>>>>>>>>>>>>>>>>>>>>> INIT RENDER
	bool correct = false;
	if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false))
		correct = Singleton<RenderManager>::instance()->initApp();
	////////temporal////////////RenderManager* renderMngr = new RenderManager(false, 800, 600, false, true, 4, false);

	if (!correct)
	{
		// Fin del renderizado
		Singleton<RenderManager>::instance()->closeApp();
		return 1;
	}

	// _RENDER_ Cacheo de objetos
	GraphicalObject* ajolote = Singleton<RenderManager>::instance()->getObject("suxalote");
	GraphicalObject* ficticioTripulacion = Singleton<RenderManager>::instance()->getObject("crew");
	GraphicalObject* tripulante_amarillo = Singleton<RenderManager>::instance()->getObject("crewmate_amongus_yellow");
	ficticioCubo = Singleton<RenderManager>::instance()->getObject("cube_empty");

	// _RENDER_ ¿ Animación para ajolote ?
	if (ajolote != nullptr)
	{
		ajolote->setAnimation("axolotl_swim");
		ajolote->animationSetEnabled(false);
		ajolote->animationSetLooping(true);
	}

	//_RENDER_ Cámara para la escena
	if (AXO_POV)
	{
		Singleton<RenderManager>::instance()->createCam(ajolote, { -25, 2, -4 });
		Singleton<RenderManager>::instance()->yawCam(90);
	}
	else
	{
		Singleton<RenderManager>::instance()->createCam(nullptr);
	}
	Singleton<RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
	Singleton<RenderManager>::instance()->objectShowMode(0);
	//>>>>>>>>>>>>>>>>>>>>>>> INIT RENDER


	//>>>>>>>>>>>>>>>>>>>>>>> INIT EC
	ec::EntityManager* entityManager = new ec::EntityManager();
	///////ecTestInit(entityManager, sampleEntity);
	sampleEntity = entityManager->addEntity();
	Mesh* sampleEntityMeshCmp = sampleEntity->addComponent<Mesh>();
	sampleEntityMeshCmp->initComponent("ejemploComponent", "cube.mesh", "logo");
	sampleEntityMeshCmp->getObj()->showDebugBox(true);
	sampleEntity->removeComponent<Mesh>();
	Fps fps;
	//>>>>>>>>>>>>>>>>>>>>>>> INIT EC


	//>>>>>>>>>>>>>>>>>>>>>>> INIT PHYSICS
	PhysicsManager::initManager();
	//>>>>>>>>>>>>>>>>>>>>>>> INIT PHYSICS

	
	//>>>>>>>>>>>>>>>>>>>>>>> INIT UI MANAGER
	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	UI_Manager* ui = new UI_Manager();
	UI_Text* testText = ui->createElement<UI_Text>("Prueba", 0.0f, 0.0f, 200.0f, 34.0f, "Arial", "Who's the impostor?", 0.5f, 0.3f, 0.1f);
	testText->setText("Ahhh yessss");
	UI_Image* testImage = ui->createElement<UI_Image>("ImgPrueba", "golf", 0.0f, 80.0f, 100.0f, 100.0f);
	UIButton* testButton = ui->createElement<UIButton>("PruebaBoton", "golf", "bubble_color", "bubble_color", 0.0f, 50.0f, 100.0f, 100.0f);
	//>>>>>>>>>>>>>>>>>>>>>>> INIT UI MANAGER


	//>>>>>>>>>>>>>>>>>>>>>>> INIT INPUT
	InputManager* input = new InputManager;
	//>>>>>>>>>>>>>>>>>>>>>>> INIT INPUT


	//>>>>>>>>>>>>>>>>>>>>>>> INIT SOUND MANAGER
	SoundManager* soundManager = new SoundManager();
	soundManager->playSound();
	//>>>>>>>>>>>>>>>>>>>>>>> INIT SOUND MANAGER


	// Bucle Principal del Motor //
	bool error = false;
	int s = 50;
	while (!input->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = (int)SDL_GetTicks(); 


		//>>>>>>>>>>>>>>>>>>>>>>> TEST PHYSICS
		miliecsSinceLastReport2 += timeSinceLastFrame;
		if (miliecsSinceLastReport2 > miliecsToReport) {
			miliecsSinceLastReport2 = 0;
			PhysicsManager::getInstance()->update();
		}
		// Para ver los couts de colisiones descomentar la s
		// s--; ඞ
		//>>>>>>>>>>>>>>>>>>>>>>> TEST PHYSICS


		//>>>>>>>>>>>>>>>>>>>>>>> TEST EC
		ecTestUpdate(entityManager, (float)timeSinceLastFrame);
		//>>>>>>>>>>>>>>>>>>>>>>> TEST EC

		//>>>>>>>>>>>>>>>>>>>>>>> TEST RENDER
		milisecsAcc += timeSinceLastFrame; 
		if (!cubeDisappearance && milisecsAcc > miliecsToDisappear) {
			bool r1, r2;
			r1 = Singleton<RenderManager>::instance()->sunsetObject("cube");
			r2 = Singleton<RenderManager>::instance()->sunsetObject("cube_empty");
			if (r1 && r2)
			{
				cubeDisappearance = true;
				ficticioCubo = nullptr;
			}
		}

		//_RENDER_ Ejemplo de movimiento: rotar objetos para ver cambios entre fotogramas

		//>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
		input->inputEvent();

		//mouseImage->setImagePosition(input->getMousePos().first, input->getMousePos().second); 
		//>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT

		if (input->isKeyDown(ScancodeKey::SCANCODE_F))
		{
			if (ficticioTripulacion != nullptr)
				ficticioTripulacion->roll(-rotationVelocity * timeSinceLastFrame);
			if (tripulante_amarillo != nullptr)
				tripulante_amarillo->yaw(rotationVelocity * timeSinceLastFrame);
		}

		if (testButton->isButtonPressed() && ajolote != nullptr)
			ajolote->yaw(rotationVelocity * timeSinceLastFrame);

		if (input->isKeyDown(ScancodeKey::SCANCODE_SPACE))
			input->showOrHideMouse(); 

		auto posMouse = input->getMousePos(); 

		if (testButton->isCursorInsideBounds(posMouse.first, posMouse.second))
		{
			testButton->cursorOnButton(); 

			if (input->isMouseDown())
			{
				testButton->mousePressedButton();
				std::cout << "Boton pulsado\n"; 
			}
		}

		else
		{
			if (testButton->isOnButton())
				testButton->mouseLeavingButton(); 
		}

		if (input->isKeyDown(ScancodeKey::SCANCODE_K))
			std::cout << "Pos Raton = " << posMouse.first << " " << posMouse.second << "\n";

		if (ficticioCubo)
			ficticioCubo->pitch(rotationVelocity * timeSinceLastFrame); 

		//_RENDER_ Prueba de animaciones
		Singleton<RenderManager>::instance()->stepAnimations(timeSinceLastFrame);

		//_RENDER_ Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame; /// Perdida de float a int
		if (miliecsSinceLastReport > miliecsToReport)
		{
			std::cout << "Objetos gráficos: " <<
				Singleton<RenderManager>::instance()->getNumObjects() << std::endl;
		}

		//_RENDER_ Control de cuándo se borran aquellos que deben ser borrados
		int f = Singleton<RenderManager>::instance()->refreshObjects();
		if (f != 0)
		{
			std::cout << f <<
				" destrucciones graficas diferidas fallidas\t/!\\" << std::endl;
		}

		//_RENDER_ Renderizar fotogramas de uno en uno
		if (!Singleton<RenderManager>::instance()->renderFrame())
			error = true;
		//>>>>>>>>>>>>>>>>>>>>>>> TEST RENDER

		fps.update();
		if (miliecsSinceLastReport > miliecsToReport) {
			testText->setText(std::to_string(fps.get()) + " fps");
			miliecsSinceLastReport = 0;
		}

		input->flush();
	}
	if (error)
	{
		std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
	}

	delete soundManager; soundManager = nullptr;
	delete input; input = nullptr;
	delete ui; ui = nullptr;
	PhysicsManager::detachManager();
	delete entityManager; entityManager = nullptr;
	// Fin del renderizado
	Singleton<RenderManager>::instance()->closeApp();
	Singleton<RenderManager>::release();

	return 0;
}

void ecTestInit(ec::EntityManager* entityManager, ec::Entity* ent) {
}
void ecTestUpdate(ec::EntityManager* entityManager, float deltaTime) {
	entityManager->update(deltaTime * 0.001f); 
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
