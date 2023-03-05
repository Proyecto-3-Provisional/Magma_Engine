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