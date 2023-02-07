#include <iostream>

#include "App.h"
#include "OgreRoot.h" // ?¿
#include "OgreLogManager.h" // ?¿

#include "SDL_timer.h"

int mainCode() {
	std::cout << "======== MAGMA iniciado ========\n";

	float lastFrameTime = SDL_GetTicks(); // Milisegundos transcurridos desde el inicio
	float timeSinceLastFrame = 0;

	App app;
	try {
		app.initApp(); // Inicio
		while (!app.salir) {
			timeSinceLastFrame = SDL_GetTicks() - lastFrameTime; // Milisegundos transcurridos desde el inicio
			lastFrameTime = SDL_GetTicks();
			///std::cout << lastFrameTime << "<--- \n";
			///std::cout << timeSinceLastFrame << "<--- \n";

			// Renderizar fotogramas de uno en uno, ya veremos si se quieren más...
			app.getRoot()->renderOneFrame(); // startRendering
			app.rotate(timeSinceLastFrame); // Rotar cubo para ver cambios entre fotogramas

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
