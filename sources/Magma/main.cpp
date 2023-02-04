#include <iostream>

#include "App.h"
#include "OgreRoot.h" // ?¿
#include "OgreLogManager.h" // ?¿

int main(int argc, char const** argv) {
	std::cout << "Hola Mundo\n";

	App app;
	try {
		app.initApp();
		app.getRoot()->startRendering();
	}
	catch (Ogre::Exception& e) {
		Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
	}
	app.closeApp();

	return 0;
}
