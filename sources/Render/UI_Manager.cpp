#include "UI_Manager.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include "UI_Text.h"
#include "UI_Image.h"

UI_Manager::UI_Manager()
{
	overlayMngr_ = Ogre::OverlayManager::getSingletonPtr();
	overlay = overlayMngr_->create("GeneralOverlay");
	
	//generalPanel = static_cast<Ogre::OverlayContainer*>(overlayMngr_->createOverlayElement("Panel", "GeneralPanel"));

	// Creamos un panel general para toda la pantalla
	/*generalPanel->setMetricsMode(Ogre::GMM_PIXELS);
	generalPanel->setPosition(0, 0);
	generalPanel->setDimensions(dimensionX, dimensionY);
	
	// Show the overlay
	overlay->add2D(generalPanel);*/
	overlay->show();
	overlay->setVisible(true);
}

UI_Manager::~UI_Manager()
{
}

void UI_Manager::init()
{
	//generalPanel->setMaterialName("BaseWhite");
	//generalPanel->setMaterialName("golf");
	/*generalPanel->setMaterialName("rat");
	*/
}

void UI_Manager::update()
{
}

/****************************************
	Borra todos los elementos del overlay
*****************************************/

void UI_Manager::cleanPanel()
{
	for (UI_Element* elem : elements)
		delete elem;
	elements.clear();
}

/****************************************************************************
	Crea un texto personalizado y lo mete a la lista de elementos del overlay
*****************************************************************************/

void UI_Manager::createText(std::string textPanelName, int posX, int posY,
	int sizeX, int sizeY, std::string fontName, std::string textContent,
	float colorX, float colorY, float colorZ)
{
	UI_Text* text = new UI_Text(overlay, textPanelName, posX, posY, sizeX, sizeY,
		fontName, textContent, Ogre::ColourValue(colorX,colorY,colorZ));
	elements.push_back(text);
}


/****************************************************************************
	Crea una imagen personalizada y la mete a la lista de elementos del overlay
*****************************************************************************/

void UI_Manager::createImage(std::string imagePanelName, std::string imageName, int posX, int posY,
	int sizeX, int sizeY)
{
	UI_Image* image = new UI_Image(overlay, imagePanelName, imageName, posX, posY, sizeX, sizeY);
	elements.push_back(image);
}

/*
UI_Element* UI_Manager::getElement(string name)
{
		
}*/
