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

	// Temporizador debug (tb para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;

	//>>>>>>>>>>>>>>>>>>>>>>> INIT RENDER
	if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false))
	{
		if (!Singleton<RenderManager>::instance()->initApp()) // if (!correct)
		{
			// Fin del renderizado
			Singleton<RenderManager>::instance()->closeApp();
			Singleton<RenderManager>::instance()->release();
			return 1;
		}
	}
	else
	{
		return 1;
	}
	//_RENDER_ Cámara y sol para la escena
	Singleton<RenderManager>::instance()->createCam(nullptr, {500, 0, 1000});
	Singleton<RenderManager>::instance()->setCamLookAt({0, 0, 0});
	Singleton<RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
	Singleton<RenderManager>::instance()->objectShowMode(0);
	//
	GraphicalObject* sol = Singleton<RenderManager>::instance()->
		addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.8f, 0.8f, 0.8f);
	sol->setDirection({ 0.0f, -0.8f, -1.0f });
	//
	GraphicalObject* equis = Singleton<RenderManager>::instance()->
		addObject("x", nullptr, "cube.mesh", "rat");
	equis->setPosition({ 400, 0, 0 });
	GraphicalObject* igriega = Singleton<RenderManager>::instance()->
		addObject("y", nullptr, "cube.mesh", "golf");
	igriega->setPosition({ 0, 400, 0 });
	GraphicalObject* ceta = Singleton<RenderManager>::instance()->
		addObject("z", nullptr, "cube.mesh", "logo");
	ceta->setPosition({ 0, 0, 400 });
	//>>>>>>>>>>>>>>>>>>>>>>> INIT RENDER


	//>>>>>>>>>>>>>>>>>>>>>>> INIT EC
	ec::EntityManager* entityManager = new ec::EntityManager();
	ec::Entity* sampleEntity = entityManager->addEntity();
	/////Transform* sampleEntityTransformCmp = sampleEntity->addComponent<Transform>(....);
	Transform* sampleEntityTransformCmp = sampleEntity->addComponent<Transform>();
	//bool trInit = sampleEntityTransformCmp->initComponent();
	sampleEntityTransformCmp->setPosition({ 0, 0, 0 });
	sampleEntityTransformCmp->setScale({ 40,40,40 });
	Mesh* sampleEntityMeshCmp = sampleEntity->addComponent<Mesh>();
	bool meshInit = sampleEntityMeshCmp->initComponent("ejemploComponent", "axolotl.mesh", "axolotl");
	if (meshInit) // hacer cosas con el cmp solo si se inicializó correctamente
	{
		sampleEntityMeshCmp->getObj()->showDebugBox(true);
		sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	}
	//sampleEntity->removeComponent<Mesh>();

	Fps fps;
	//>>>>>>>>>>>>>>>>>>>>>>> INIT EC


	//>>>>>>>>>>>>>>>>>>>>>>> INIT PHYSICS
	bool correct = false;
	if (Singleton<PhysicsManager>::init())
		correct = Singleton<PhysicsManager>::instance()->initPhysics();
	////////temporal////////////RenderManager* renderMngr = new RenderManager(false, 800, 600, false, true, 4, false);

	if (!correct)
	{
		// Fin del renderizado
		Singleton<PhysicsManager>::instance()->detachPhysics();
		return 1;
	}
	//>>>>>>>>>>>>>>>>>>>>>>> INIT PHYSICS

	
	//>>>>>>>>>>>>>>>>>>>>>>> INIT UI MANAGER
	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	UI_Manager* ui = new UI_Manager();
	UI_Text* testText = ui->createElement<UI_Text>("Prueba", 0.0f, 0.0f, 200.0f, 34.0f, "Arial", "Who's the impostor?", 0.5f, 0.3f, 0.1f);
	testText->setText("Ahhh yessss");
	UI_Image* testImage = ui->createElement<UI_Image>("ImgPrueba", "golf", 0.0f, 80.0f, 100.0f, 100.0f);
	UIButton* testButton = ui->createElement<UIButton>("PruebaBoton", "golf", "bubble_color", "bubble_color", 0.0f, 30.0f, 100.0f, 100.0f);
	//>>>>>>>>>>>>>>>>>>>>>>> INIT UI MANAGER


	//>>>>>>>>>>>>>>>>>>>>>>> INIT INPUT
	InputManager* input = new InputManager;
	//>>>>>>>>>>>>>>>>>>>>>>> INIT INPUT

	//>>>>>>>>>>>>>>>>>>>>>>> INIT SOUND MANAGER
	//SoundManager* soundManager = new SoundManager();
	//soundManager->addSong(".\executables\assets\loop.wav", 35, 1, true); 
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
			Singleton<PhysicsManager>::instance()->update();
		}
		// Para ver los couts de colisiones descomentar la s
		// s--; ඞ
		//>>>>>>>>>>>>>>>>>>>>>>> TEST PHYSICS


		// vvvvvvvvvvvvvvvvvvvvvvv TEST EC
		entityManager->update(timeSinceLastFrame * 0.001f);	//ecTestUpdate
		entityManager->refresh();							//ecTestUpdate
		sampleEntityTransformCmp->yaw(1);					//rotado con referencia al componente transform
		sampleEntity->getComponent<Transform>()->roll(1);	//rotado pidiendo la referencia al componente transform
		// ʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌʌ TEST EC


		//>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
		input->inputEvent();
		//mouseImage->setImagePosition(input->getMousePos().first, input->getMousePos().second); 
		//>>>>>>>>>>>>>>>>>>>>>>> TEST INPUT
	
		if (sampleEntityMeshCmp/* && trInit */&& meshInit)
		{
			// esta rotación DEBERÍA HACERSE según Transform
			//sampleEntityTransformCmp->setRotation(/*LIADA_MASIVA*/)
			//sampleEntityMeshCmp->getObj()->yaw(rotationVelocity * timeSinceLastFrame);
			sampleEntityTransformCmp->setVelocity({ 0, 0, 25 });
			//sampleEntityTransformCmp->yaw(10);
		}

		//if (testButton->isButtonPressed()) // para saber si "la palanca fue activada" (toggle)
			//std::cout << "pasan cosas..." << std::endl; //		🦍

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

		if (input->hasWindowChange()) {
			Singleton<RenderManager>::instance()->notifyWindowResized();
			testImage->updateImage();
			testButton->updateButton();
			testText->updateText();
		}

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

	//delete soundManager; soundManager = nullptr;
	delete input; input = nullptr;
	delete ui; ui = nullptr;
	Singleton<PhysicsManager>::instance()->detachPhysics();
	Singleton<PhysicsManager>::release();
	delete entityManager; entityManager = nullptr;
	// Fin del renderizado
	Singleton<RenderManager>::instance()->closeApp();
	Singleton<RenderManager>::release();

	return 0;
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
