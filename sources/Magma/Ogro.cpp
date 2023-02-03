#include "Ogro.h"

#include <Ogre.h>
#include <OgreFileSystemLayer.h>
#include <Overlay/OgreOverlaySystem.h>
#include <Overlay/OgreOverlayManager.h>
// v- nos aprovechamos de los residuos de la solución que compiló a OGRE -v
#include <SDL.h> // /!\ SOBREESCRIBE AL main()
#include <SDL_syswm.h>
#include <iostream>

void Ogro::construye() {
	// ENCENDEMOS
	Ogre::String cadenaOgro = "HOLA_OGRO\n";
	std::cout << cadenaOgro;
}

void Ogro::destruye() {
	// APAGAMOS
	std::cout << "ADIOS_OGRO\n";
}
