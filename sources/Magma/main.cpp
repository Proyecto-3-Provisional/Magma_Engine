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
#include <EC/progress_bar.h>
#include <EC/timer.h>
#include <EC/player_controller.h>
#include <Render/image.h>
#include <Render/text.h>
#include <Render/button.h>
#include <Sounds/audio_source.h>
#include <EC/factory_manager.h>
#include <EC/init_factories.h>
#include <Lua/scene_loader.h>


// DECLARACIÓN DE FUNCIONES
void initManagers();
void releaseManagers();

int mainCode() {
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//
#ifdef _DEBUG

#if 1 // por comodidad (0 -> false; No 0 -> true)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else	
	_CrtSetBreakAlloc(996); // id del new que queremos borrar
#endif
#endif
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//

	// Temporizador debug (también para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	// Carga de mapa
	Singleton<magma_engine::SceneLoader>::init();
	Singleton<magma_engine::SceneLoader>::instance()->loadScene("assets/scenes/test.magmascene");
	Singleton<magma_engine::SceneLoader>::release();
	// Carga de mapa

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;

	// ---------- Inicialización MANAGERS ----------

	initManagers();

	magma_engine::setUpFactories();

	std::cout << "Managers inicializados\n";

	// ---------- Inicialización RENDER ----------

	// Cámara
	Singleton<magma_engine::RenderManager>::instance()->createCam(nullptr, { 0, 1000, 0 });
	Singleton<magma_engine::RenderManager>::instance()->setCamLookAt({ 0, -1000, 0 });
	Singleton<magma_engine::RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
	Singleton<magma_engine::RenderManager>::instance()->objectShowMode(0);

	// Sol
	magma_engine::GraphicalObject* sol = Singleton<magma_engine::RenderManager>::instance()->
		addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.8f, 0.8f, 0.8f);
	sol->setDirection({ 0.0f, -1.0f, 0.0f }, true);
	
	// Fondo
	magma_engine::GraphicalObject* lavaBg = Singleton<magma_engine::RenderManager>::instance()->
		addObject("background", nullptr, "mPlane1080x800", "magma_background");
	lavaBg->setScale(1.67);	// Adaptar segun viewport camara
	lavaBg->setPosition({ 0, -225, 0 });
	lavaBg->yaw(90);

	// ---------- Inicialización EC ----------

	magma_engine::ec::Entity* physicsEntity = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Transform", physicsEntity);
	//physicsEntity->addC<Transform>(Singleton<FactoryManager>::instance()->findAndCreate("Transform"));
	//physicsEntity->getComponent<magma_engine::Transform>()->initComponent({ 0, 0, 0 }, { 40,40,40 });

	Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Mesh", physicsEntity);
	bool meshInit2 = physicsEntity->getComponent<magma_engine::Mesh>()->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");

	magma_engine::Rigidbody* physicsEntityRigidbodyCmp = physicsEntity->addComponent<magma_engine::Rigidbody>();
	bool eliminar = physicsEntity->getComponent<magma_engine::Rigidbody>()->initComponent();

	
	/*ec::Entity* physicsEntity = Singleton<ec::EntityManager>::instance()->addEntity();
	Transform* physicsEntityTransformCmp = physicsEntity->addComponent<Transform>();
	physicsEntityTransformCmp->setPosition({ 0, 0, 0 });
	physicsEntityTransformCmp->setScale({ 40,40,40 });
	Mesh* physicsEntityMeshCmp = physicsEntity->addComponent<Mesh>();
	bool meshInit2 = physicsEntityMeshCmp->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");*/
	// hacer cosas con el cmp solo si se inicializó correctamente
	if (meshInit2)
	{
		//sampleEntityMeshCmp->getObj()->showDebugBox(true);
		//sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	}
	//Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("Mesh", physicsEntity);
	//bool meshInit2 = physicsEntity->getComponent<magma_engine::Mesh>()->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");
	//if (meshInit2)
	//{
	//	//sampleEntityMeshCmp->getObj()->showDebugBox(true);
	//	//sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	//}

	magma_engine::ec::Entity* physicsEntity2 = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	magma_engine::Transform* physicsEntityTransformCmp2 = physicsEntity2->addComponent<magma_engine::Transform>();
	physicsEntityTransformCmp2->setPosition({ 500, 0, 0 });
	physicsEntityTransformCmp2->setScale({ 40,40,40 });
	magma_engine::Mesh* physicsEntityMeshCmp2 = physicsEntity2->addComponent<magma_engine::Mesh>();
	bool meshInit3 = physicsEntityMeshCmp2->initComponent("ejemploPhysics2", "axolotl.mesh", "axolotl");
	// hacer cosas con el cmp solo si se inicializó correctamente
	if (meshInit3)
	{
		physicsEntityMeshCmp2->getObj()->showDebugBox(true);
		physicsEntityMeshCmp2->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, magma_engine::Vector3D(1, 0, 0));
	}
	magma_engine::Rigidbody* physicsEntityRigidbodyCmp2 = physicsEntity2->addComponent<magma_engine::Rigidbody>();

	magma_engine::ec::Entity* physicsEntity3 = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();
	magma_engine::Transform* physicsEntityTransformCmp3 = physicsEntity3->addComponent<magma_engine::Transform>();
	physicsEntityTransformCmp3->setPosition({ -500, 0, 0 });
	physicsEntityTransformCmp3->setScale({ 40,40,40 });
	magma_engine::Mesh* physicsEntityMeshCmp3 = physicsEntity3->addComponent<magma_engine::Mesh>();
	bool meshInit4 = physicsEntityMeshCmp3->initComponent("ejemploPhysics3", "axolotl.mesh", "axolotl");
	// hacer cosas con el cmp solo si se inicializó correctamente
	if (meshInit4)
	{
		physicsEntityMeshCmp3->getObj()->showDebugBox(true);
		physicsEntityMeshCmp3->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, magma_engine::Vector3D(1, 0, 0));
	}
	magma_engine::Rigidbody* physicsEntityRigidbodyCmp3 = physicsEntity3->addComponent<magma_engine::Rigidbody>();
	Singleton<magma_engine::FactoryManager>::instance()->findAndCreate("PlayerController", physicsEntity3);
	physicsEntity3->getComponent<magma_engine::PlayerController>()->initComponent(50000.0f, 1.0f);


	magma_engine::Fps fps;

	// ---------- Inicialización UI ----------

	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	/*UI_Text* testText = Singleton<UI_Manager>::instance()->createElement<UI_Text>("Prueba", 0.0f, 0.0f, 200.0f, 34.0f, "arial", "Who's the impostor?", 0.5f, 0.3f, 0.1f);
	testText->setText("Ahhh yessss");
	UI_Image* testImage = Singleton<UI_Manager>::instance()->createElement<UI_Image>("ImgPrueba", "golf", 0.0f, 80.0f, 100.0f, 100.0f);
	UIButton* testButton = Singleton<UI_Manager>::instance()->createElement<UIButton>("PruebaBoton", "golf", "bubble_color", "bubble_color", 0.0f, 30.0f, 100.0f, 100.0f);*/

	magma_engine::ec::Entity* imageEntity = Singleton<magma_engine::ec::EntityManager>::instance()->addEntity();

	float progreso = 20.0f; 

	magma_engine::Text* componentTextEntity = imageEntity->addComponent<magma_engine::Text>();
	componentTextEntity->initComponent("Prueba", "PruebaTexto", "arial", "It's working? Yessssss", 0.0f, 0.0f, 200.0f, 34.0f, 0.5f, 0.3f, 0.1f);
	componentTextEntity->start();

	magma_engine::Button* componentButtonEntity = imageEntity->addComponent<magma_engine::Button>();
	componentButtonEntity->initComponent("ButtonPrueba", "button_solid", "button_transparent", "bubble", 100.0f, 50.0f, 0.0f, 0.0f);
	componentButtonEntity->start();

	magma_engine::Image* componentImageEntity = imageEntity->addComponent<magma_engine::Image>();
	componentImageEntity->initComponent("ImgPrueba", "bubble", 200.0f, 200.0f, 100.0f, 100.0f);
	componentImageEntity->start();

	// Botones volumenes
	magma_engine::Button* componentButtonVolEntity = imageEntity->addComponent<magma_engine::Button>();
	componentButtonVolEntity->initComponent("ButtonDownVol", "buttonVol1_solid", "buttonVol1_solid", "buttonVol1_transparent", 50.0f, 50.0f, 350.0f, 350.0f);
	componentButtonVolEntity->start();

	magma_engine::Button* componentButtonVol2Entity = imageEntity->addComponent<magma_engine::Button>();
	componentButtonVol2Entity->initComponent("ButtonUpVol", "buttonVol2_solid", "buttonVol2_solid", "buttonVol2_transparent", 50.0f, 50.0f, 650.0f, 350.0f);
	componentButtonVol2Entity->start();

	magma_engine::AudioSource* componentSoundEffect = imageEntity->addComponent<magma_engine::AudioSource>();
	componentSoundEffect->initComponent("./assets/sounds/eat.wav", 50, 3, false, false);
	componentSoundEffect->start();

	magma_engine::AudioSource* componentSound = imageEntity->addComponent<magma_engine::AudioSource>();
	componentSound->initComponent("./assets/sounds/popcorn.wav", 50, 2, true, true);
	componentSound->start();
	
	

	/*magma_engine::Progress_Bar* componentProgress = imageEntity->addComponent<magma_engine::Progress_Bar>();
	componentProgress->initComponent("ImgPrueba", "golf", 50.0f, 50.0f, 200.0f, 200.0f, progreso, 300.0f);
	componentProgress->start();

	magma_engine::Timer* timeComponent = imageEntity->addComponent<magma_engine::Timer>();
	timeComponent->initComponent();
	timeComponent->start();*/

	// ---------- BUCLE PRINCIPAL ----------
	bool error = false;
	int s = 50;
	while (!Singleton<magma_engine::InputManager>::instance()->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = (int)SDL_GetTicks();

		// ---------- TEST RENDER ----------

		//Prueba de animaciones
		Singleton<magma_engine::RenderManager>::instance()->stepAnimations(timeSinceLastFrame);
		//Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport)
		{
			std::cout << "Objetos gráficos: " <<
				Singleton<magma_engine::RenderManager>::instance()->getNumObjects() << std::endl;
		}
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

		// ---------- TEST EC ----------
		Singleton<magma_engine::ec::EntityManager>::instance()->update(timeSinceLastFrame * 0.001f);
		Singleton<magma_engine::ec::EntityManager>::instance()->refresh();


		// ---------- TEST PHYSICS ----------

		//miliecsSinceLastReport2 += timeSinceLastFrame;
		//if (miliecsSinceLastReport2 > miliecsToReport) {
		//	miliecsSinceLastReport2 = 0;
		//}
		Singleton<magma_engine::PhysicsManager>::instance()->update(timeSinceLastFrame * 0.001f);
		if (eliminar) {
			if (physicsEntityRigidbodyCmp->isOnCollision()) {
				physicsEntity->setAlive(false);
				eliminar = false;
			}
		}

		// ---------- TEST INPUT & UI ----------update
		Singleton<magma_engine::InputManager>::instance()->inputEvent();
		physicsEntity3->getComponent<magma_engine::PlayerController>()->update(timeSinceLastFrame * 0.001f);

		//mouseImage->setImagePosition(input->getMousePos().first, input->getMousePos().second); 

		if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_SPACE))
		{
			/*progreso += 5.0f;
			componentProgress->setProgress(progreso);

			timeComponent->pause(); */
			componentSoundEffect->playSong();

		}

		/*else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_O))
		{
			timeComponent->resume();
		}

		else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_I))
		{
			timeComponent->reset();
		}

		else if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_P))
		{
			timeComponent->assignText(componentTextEntity);
		}*/

		auto posMouse = Singleton<magma_engine::InputManager>::instance()->getMousePos();

		/*if (testButton->isCursorInsideBounds(posMouse.first, posMouse.second))
		{
			testButton->cursorOnButton();

			if (Singleton<InputManager>::instance()->isMouseDown())
			{
				testButton->mousePressedButton();
				std::cout << "Boton pulsado\n";
			}
		}
		else
		{
			if (testButton->isOnButton())
				testButton->mouseLeavingButton();
		}*/

		if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_K))
			std::cout << "Pos Raton = " << posMouse.first << " " << posMouse.second << "\n";

		//Redimensión ventana
		if (Singleton<magma_engine::InputManager>::instance()->hasWindowChange()) {
			Singleton<magma_engine::RenderManager>::instance()->notifyWindowResized();
			/*testImage->updateImage();
			testButton->updateButton();
			testText->updateText();*/
			//imageEntity->update(timeSinceLastFrame * 0.001f);
		}

		//esto hace que ya pille bien el imput la ui al pulsar el raton
		imageEntity->update(timeSinceLastFrame * 0.001f);
		//si dejo descomentado esto de abajo no me hace falta lo de arriba pero necesito confirmacion de los compañeros
		// ---------- TEST EC ----------
		//Singleton<ec::EntityManager>::instance()->update(timeSinceLastFrame * 0.001f);	
		//Singleton<ec::EntityManager>::instance()->refresh();

		Singleton<magma_engine::InputManager>::instance()->flush();

		// ---------- FPS CALCULATOR ----------
		fps.update();

		if (miliecsSinceLastReport > miliecsToReport) {
			//testText->setText(std::to_string(fps.get()) + " fps");
			miliecsSinceLastReport = 0;
		}
		
		

	}
	if (error)
	{
		std::cout << "****** ****** ERROR DE FOTOGRAMA ****** ******\n";
	}

	// ---------- Release MANAGERS ----------
	releaseManagers();

	return 0;
}

void initManagers() {

	// ------ RENDER ------
	if (Singleton<magma_engine::RenderManager>::init(false, 1280, 720, false, true, 4, false))
	{
		if (!Singleton<magma_engine::RenderManager>::instance()->initApp()) // if (!correct)
		{
			// Fin del renderizado
			Singleton<magma_engine::RenderManager>::instance()->closeApp();
			Singleton<magma_engine::RenderManager>::instance()->release();
		}
	}

	// ------ EC ------
	Singleton<magma_engine::ec::EntityManager>::init();

	// ------ PHYSICS ------
	bool correct = false;
	if (Singleton<magma_engine::PhysicsManager>::init())
		correct = Singleton<magma_engine::PhysicsManager>::instance()->initPhysics();

	if (!correct)
	{
		// Fin del renderizado
		Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	}

	// ------ UI ------
	Singleton<magma_engine::UI_Manager>::init();

	// ------ INPUT ------
	Singleton<magma_engine::InputManager>::init();

	// ------ SOUND ------
	if(Singleton<magma_engine::SoundManager>::init())
		Singleton<magma_engine::SoundManager>::instance()->initAudio();

	// ------ FACTORY ------
	Singleton<magma_engine::FactoryManager>::init();


}

void releaseManagers() {

	// ------ EC ------
	Singleton<magma_engine::ec::EntityManager>::release();

	// ------ PHYSICS ------
	Singleton<magma_engine::PhysicsManager>::instance()->detachPhysics();
	Singleton<magma_engine::PhysicsManager>::release();

	// ------ INPUT ------
	Singleton<magma_engine::InputManager>::release();

	// ------ UI ------
	Singleton<magma_engine::UI_Manager>::release();

	// ------ RENDER ------
	Singleton<magma_engine::RenderManager>::instance()->closeApp();
	Singleton<magma_engine::RenderManager>::release();

	// ------ SOUND ------
	Singleton<magma_engine::SoundManager>::release();

	// ------ FACTORY ------
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
