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
#include <EC/image.h>
#include <EC/text.h>
#include <EC/audio_source.h>
#include <Magma/factory_manager.h>
#include <Magma/init_factories.h>
#include <LuaBridge/lua_main.h>


// DECLARACIÓN DE FUNCIONES
void initManagers();
void releaseManagers();

int mainCode() {
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//
#ifdef _DEBUG

#if 1 // por comodidad (0 -> false; No 0 -> true)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else	
	_CrtSetBreakAlloc(34613); // id del new que queremos borrar
#endif
#endif
	//\\//\\//\\//\\// Comprobación Fugas Memoria //\\//\\//\\//\\//

	// Temporizador debug (también para físicas)
	const int miliecsToReport = 5000;
	int miliecsSinceLastReport = 0;
	int miliecsSinceLastReport2 = 0;
	//=====================

	std::cout << "======== MAGMA iniciado ========\n";

	luaMain();

	// Marca de tiempo del último fotograma, en milisegundos transcurridos desde el inicio
	int lastFrameTime = (int)SDL_GetTicks(); // uint32 a int
	// Cálculo del tiempo, en milisegundos, entre fotogramas
	int timeSinceLastFrame = 0;

	// ---------- Inicialización MANAGERS ----------

	initManagers();

	setUpFactories();

	std::cout << "Managers inicializados\n";

	// ---------- Inicialización RENDER ----------

	//Cámara
	Singleton<RenderManager>::instance()->createCam(nullptr, { 0, 0, 1000 });
	Singleton<RenderManager>::instance()->setCamLookAt({ 0, 0, 0 });
	Singleton<RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
	Singleton<RenderManager>::instance()->objectShowMode(0);

	//Sol
	GraphicalObject* sol = Singleton<RenderManager>::instance()->
		addObject("sol", nullptr, "SUN");
	sol->setLightColor(0.8f, 0.8f, 0.8f);
	sol->setDirection({ 0.0f, -0.8f, -1.0f });

	GraphicalObject* equis = Singleton<RenderManager>::instance()->
		addObject("x", nullptr, "cube.mesh", "rat");
	equis->setPosition({ 400, 0, 0 });
	GraphicalObject* igriega = Singleton<RenderManager>::instance()->
		addObject("y", nullptr, "cube.mesh", "golf");
	igriega->setPosition({ 0, 400, 0 });
	GraphicalObject* ceta = Singleton<RenderManager>::instance()->
		addObject("z", nullptr, "cube.mesh", "logo");
	ceta->setPosition({ 0, 0, 400 });

	// ---------- Inicialización EC ----------

	//ec::Entity* sampleEntity = Singleton<ec::EntityManager>::instance()->addEntity();
	//Transform* sampleEntityTransformCmp = sampleEntity->addComponent<Transform>();
	//sampleEntityTransformCmp->setPosition({ 0, 0, 0 });
	//sampleEntityTransformCmp->setScale({ 40,40,40 });
	//Mesh* sampleEntityMeshCmp = sampleEntity->addComponent<Mesh>();
	//bool meshInit = sampleEntityMeshCmp->initComponent("ejemploComponent", "axolotl.mesh", "axolotl");
	//// hacer cosas con el cmp solo si se inicializó correctamente
	//if (meshInit)
	//{
	//	sampleEntityMeshCmp->getObj()->showDebugBox(true);
	//	sampleEntityMeshCmp->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	//}

	ec::Entity* physicsEntity = Singleton<ec::EntityManager>::instance()->addEntity();
	Singleton<FactoryManager>::instance()->findAndCreate("Transform", physicsEntity);
	//physicsEntity->addC<Transform>(Singleton<FactoryManager>::instance()->findAndCreate("Transform"));
	physicsEntity->getComponent<Transform>()->setPosition({ 0, 0, 0 });
	physicsEntity->getComponent<Transform>()->setScale({ 40,40,40 });
	Singleton<FactoryManager>::instance()->findAndCreate("Mesh", physicsEntity);
	bool meshInit2 = physicsEntity->getComponent<Mesh>()->initComponent("ejemploPhysics", "axolotl.mesh", "axolotl");
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
	Rigidbody* physicsEntityRigidbodyCmp = physicsEntity->addComponent<Rigidbody>(Vector3D(70, 40, 40));
	bool eliminar = true;

	ec::Entity* physicsEntity2 = Singleton<ec::EntityManager>::instance()->addEntity();
	Transform* physicsEntityTransformCmp2 = physicsEntity2->addComponent<Transform>();
	physicsEntityTransformCmp2->setPosition({ 500, 0, 0 });
	physicsEntityTransformCmp2->setScale({ 40,40,40 });
	Mesh* physicsEntityMeshCmp2 = physicsEntity2->addComponent<Mesh>();
	bool meshInit3 = physicsEntityMeshCmp2->initComponent("ejemploPhysics2", "axolotl.mesh", "axolotl");
	// hacer cosas con el cmp solo si se inicializó correctamente
	if (meshInit3)
	{
		physicsEntityMeshCmp2->getObj()->showDebugBox(true);
		physicsEntityMeshCmp2->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	}
	Rigidbody* physicsEntityRigidbodyCmp2 = physicsEntity2->addComponent<Rigidbody>(Vector3D(70, 40, 40));
	physicsEntityRigidbodyCmp2->addForce(Vector3D(-500, 0, 0));

	ec::Entity* physicsEntity3 = Singleton<ec::EntityManager>::instance()->addEntity();
	Transform* physicsEntityTransformCmp3 = physicsEntity3->addComponent<Transform>();
	physicsEntityTransformCmp3->setPosition({ -500, 0, 0 });
	physicsEntityTransformCmp3->setScale({ 40,40,40 });
	Mesh* physicsEntityMeshCmp3 = physicsEntity3->addComponent<Mesh>();
	bool meshInit4 = physicsEntityMeshCmp3->initComponent("ejemploPhysics3", "axolotl.mesh", "axolotl");
	// hacer cosas con el cmp solo si se inicializó correctamente
	if (meshInit4)
	{
		physicsEntityMeshCmp3->getObj()->showDebugBox(true);
		physicsEntityMeshCmp3->getObj()->setOriLookingAt({ 0, 0, 1000 }, Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	}
	Rigidbody* physicsEntityRigidbodyCmp3 = physicsEntity3->addComponent<Rigidbody>(Vector3D(70, 40, 40));
	physicsEntityRigidbodyCmp3->addForce(Vector3D(500, 0, 0));

	Fps fps;

	// ---------- Inicialización UI ----------

	// UI Manager (Para que funcione, es necesario que render_manager se haya ejecutado antes)
	/*UI_Text* testText = Singleton<UI_Manager>::instance()->createElement<UI_Text>("Prueba", 0.0f, 0.0f, 200.0f, 34.0f, "Arial", "Who's the impostor?", 0.5f, 0.3f, 0.1f);
	testText->setText("Ahhh yessss");
	UI_Image* testImage = Singleton<UI_Manager>::instance()->createElement<UI_Image>("ImgPrueba", "golf", 0.0f, 80.0f, 100.0f, 100.0f);
	UIButton* testButton = Singleton<UI_Manager>::instance()->createElement<UIButton>("PruebaBoton", "golf", "bubble_color", "bubble_color", 0.0f, 30.0f, 100.0f, 100.0f);*/

	ec::Entity* imageEntity = Singleton<ec::EntityManager>::instance()->addEntity();
	Image* componentImageEntity = imageEntity->addComponent<Image>
		("ImgPrueba", "bubble", 200.0f, 200.0f, 100.0f, 100.0f);
	componentImageEntity->start();

	Text* componentTextEntity = imageEntity->addComponent<Text>
		("Prueba", "PruebaTexto", "Arial", "It's working? Yessssss", 0.0f, 0.0f, 200.0f, 34.0f, 0.5f, 0.3f, 0.1f);
	componentTextEntity->start();

	// ---------- Inicialización SOUND ----------
	Singleton<SoundManager>::instance()->initAudio();
	Singleton<SoundManager>::instance()->loadWAV("./assets/loop.wav", 50, 2, true);
	Singleton<SoundManager>::instance()->playSound(2);



	// ---------- BUCLE PRINCIPAL ----------
	bool error = false;
	int s = 50;
	while (!Singleton<InputManager>::instance()->exitRequested() && !error && s > 0)
	{
		// Marcas de tiempo y cálculo del "delta"
		timeSinceLastFrame = SDL_GetTicks() - lastFrameTime;
		lastFrameTime = (int)SDL_GetTicks();

		// ---------- TEST RENDER ----------

		//Prueba de animaciones
		Singleton<RenderManager>::instance()->stepAnimations(timeSinceLastFrame);
		//Imprimir número de objetos gráficos cada cierto tiempo
		miliecsSinceLastReport += timeSinceLastFrame;
		if (miliecsSinceLastReport > miliecsToReport)
		{
			std::cout << "Objetos gráficos: " <<
				Singleton<RenderManager>::instance()->getNumObjects() << std::endl;
		}
		//Control de cuándo se borran aquellos que deben ser borrados
		int f = Singleton<RenderManager>::instance()->refreshObjects();
		if (f != 0)
		{
			std::cout << f <<
				" destrucciones graficas diferidas fallidas\t/!\\" << std::endl;
		}
		//Renderizar fotogramas de uno en uno
		if (!Singleton<RenderManager>::instance()->renderFrame())
			error = true;

		// ---------- TEST EC ----------
		Singleton<ec::EntityManager>::instance()->update(timeSinceLastFrame * 0.001f);	
		Singleton<ec::EntityManager>::instance()->refresh();


		// ---------- TEST PHYSICS ----------

		//miliecsSinceLastReport2 += timeSinceLastFrame;
		//if (miliecsSinceLastReport2 > miliecsToReport) {
		//	miliecsSinceLastReport2 = 0;
		//}
		Singleton<PhysicsManager>::instance()->update(timeSinceLastFrame * 0.001f);
		if (eliminar) {
			if (physicsEntityRigidbodyCmp->isOnCollision()) {
				physicsEntity->setAlive(false);
				eliminar = false;
			}
		}

		// ---------- TEST INPUT & UI ----------
		Singleton<InputManager>::instance()->inputEvent();
		//mouseImage->setImagePosition(input->getMousePos().first, input->getMousePos().second); 

		if (Singleton<InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_SPACE))
			Singleton<InputManager>::instance()->showOrHideMouse();

		auto posMouse = Singleton<InputManager>::instance()->getMousePos();

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

		if (Singleton<InputManager>::instance()->isKeyDown(ScancodeKey::SCANCODE_K))
			std::cout << "Pos Raton = " << posMouse.first << " " << posMouse.second << "\n";

		//Redimensión ventana
		if (Singleton<InputManager>::instance()->hasWindowChange()) {
			Singleton<RenderManager>::instance()->notifyWindowResized();
			/*testImage->updateImage();
			testButton->updateButton();
			testText->updateText();*/
			imageEntity->update(timeSinceLastFrame * 0.001f);
		}


		Singleton<InputManager>::instance()->flush();

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
	if (Singleton<RenderManager>::init(false, 1280, 720, false, true, 4, false))
	{
		if (!Singleton<RenderManager>::instance()->initApp()) // if (!correct)
		{
			// Fin del renderizado
			Singleton<RenderManager>::instance()->closeApp();
			Singleton<RenderManager>::instance()->release();
		}
	}

	// ------ EC ------
	Singleton<ec::EntityManager>::init();

	// ------ PHYSICS ------
	bool correct = false;
	if (Singleton<PhysicsManager>::init())
		correct = Singleton<PhysicsManager>::instance()->initPhysics();

	if (!correct)
	{
		// Fin del renderizado
		Singleton<PhysicsManager>::instance()->detachPhysics();
	}

	// ------ UI ------
	Singleton<UI_Manager>::init();

	// ------ INPUT ------
	Singleton<InputManager>::init();

	// ------ SOUND ------
	Singleton<SoundManager>::init();

	// ------ FACTORY ------
	Singleton<FactoryManager>::init();


}

void releaseManagers() {

	// ------ EC ------
	Singleton<ec::EntityManager>::release();

	// ------ PHYSICS ------
	Singleton<PhysicsManager>::instance()->detachPhysics();
	Singleton<PhysicsManager>::release();

	// ------ INPUT ------
	Singleton<InputManager>::release();

	// ------ UI ------
	Singleton<UI_Manager>::release();

	// ------ RENDER ------
	Singleton<RenderManager>::instance()->closeApp();
	Singleton<RenderManager>::release();

	// ------ SOUND ------
	Singleton<SoundManager>::release();

	// ------ FACTORY ------
	Singleton<FactoryManager>::release();

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
