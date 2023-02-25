#include "UI_Manager.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>


#include "UI_Text.h"

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
}

UI_Manager::~UI_Manager() {}

void UI_Manager::init()
{
	//generalPanel->setMaterialName("BaseWhite");
	//generalPanel->setMaterialName("golf");
	/*generalPanel->setMaterialName("rat");

	*/
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

void UI_Manager::createText(string textPanelName, int posX, int posY, int sizeX, int sizeY, string fontName, string textContent,float colorX, float colorY, float colorZ)
{
	UI_Text* text = new UI_Text(overlay, textPanelName, posX, posY, sizeX, sizeY, fontName, textContent, Ogre::ColourValue(colorX,colorY,colorZ));
	elements.push_back(text);
}

UI_Element* UI_Manager::getElement(string name)
{

}
