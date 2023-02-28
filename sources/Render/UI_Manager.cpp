#include "UI_Manager.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include "UI_Text.h"
#include "UI_Image.h"

/*************************************************
	Creamos un overlay y lo mostramos en pantalla
**/
UI_Manager::UI_Manager()
{
	overlayMngr_ = Ogre::OverlayManager::getSingletonPtr();
	overlay = overlayMngr_->create("GeneralOverlay");
	overlay->setVisible(true);
	overlay->show();
}

UI_Manager::~UI_Manager()
{
}

void UI_Manager::init()
{}

void UI_Manager::update()
{}

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


UI_Element* UI_Manager::getElement(std::string name)
{
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i]->getElementName() == name) {
			
			return elements[i];
		}
	}
}
