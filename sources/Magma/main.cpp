#include <iostream>

#include "App.h"
#include "OgreRoot.h" // ?¿
#include "OgreLogManager.h" // ?¿

int mainCode() {
	std::cout << "Hola Mundo\n";

	App app;
	try {
		app.initApp(); // Inicio
		while (!app.salir) {
			// Renderizar fotogramas de uno en uno, ya veremos si se quieren más...
			app.getRoot()->renderOneFrame(); // startRendering
			app.rotate(); // Rotar cubo para ver cambios entre fotogramas
		}
	}
	catch (Ogre::Exception& e) {
		Ogre::String errMsg = "An exception has occured: " + e.getFullDescription() + "\n";
		Ogre::LogManager::getSingleton().logMessage(errMsg);
	}
	app.closeApp(); // Fin

	return 0;
}

#if _DEBUG
int main(int argc, char const** argv) {
	return mainCode();
}
#else
int __stdcall WinMain(void*, void*, char* cmdLine, int) {
	return mainCode();
}
#endif
