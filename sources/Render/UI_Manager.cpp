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
	Crea una imagen personalizada y la mete a la lista de elementos del overlay
*****************************************************************************/

void UI_Manager::createImage(std::string imagePanelName, std::string imageName, int posX, int posY,
	int sizeX, int sizeY)
{
	UI_Image* image = new UI_Image(overlay, imagePanelName, imageName, posX, posY, sizeX, sizeY);
	elements.push_back(image);
}
