// Fugas Memoria
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include <iostream>
#include <windows.h>

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

#include <MagmaEngine/MagmaEngine.h>

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

	std::cout << "======== MAGMA iniciado ========\n";

	magma_engine::CMagmaEngine motor = magma_engine::CMagmaEngine();
	if(motor.Init())
	{
		motor.run();
		motor.ShutDown();
	}

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
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
	return mainCode();
}
#endif
