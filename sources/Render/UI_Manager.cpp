#include "UI_Manager.h"

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>

UI_Manager::UI_Manager(int dimensionX, int dimensionY)
{
	overlayMngr_ = Ogre::OverlayManager::getSingletonPtr();
	Ogre::Overlay* overlay = overlayMngr_->create("OverlayName");
	
	generalPanel = static_cast<Ogre::OverlayContainer*>(overlayMngr_->createOverlayElement("Panel", "GeneralPanel"));

	// Creamos un panel general para toda la pantalla
	generalPanel->setMetricsMode(Ogre::GMM_PIXELS);
	generalPanel->setPosition(0, 0);
	generalPanel->setDimensions(dimensionX, dimensionY);
	
	// Show the overlay
	overlay->add2D(generalPanel);
	overlay->show();
}

UI_Manager::~UI_Manager() {}

void UI_Manager::init()
{
	generalPanel->setMaterialName("BaseWhite");

	// Creamos un area de texto sobre la que trabajar
	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayMngr_->createOverlayElement("TextArea", "TextAreaUI"));

	// Preparar dimensiones y contenido texto
	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(0, 0);
	textArea->setDimensions(100, 100);
	textArea->setCaption("Creo que Eva es sospechosa");

	// Tamaño letra, fuente y color
	textArea->setCharHeight(16);

	textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));

	//textArea->setFontName("BlueHighway"); // Falla al no haber carga de recursos, especificamente con ttf

	generalPanel->addChild(textArea);

}

