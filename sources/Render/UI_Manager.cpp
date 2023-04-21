#include "UI_Manager.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <Render/ui_text.h>
#include <Render/ui_image.h>

namespace magma_engine
{
	UI_Manager::UI_Manager()
	{
		overlayMngr_ = Ogre::OverlayManager::getSingletonPtr();
		overlay = overlayMngr_->create("GeneralOverlay");
		overlay->setVisible(true);
		overlay->show();
	}

	UI_Manager::~UI_Manager()
	{
		cleanPanel();

		overlayMngr_->destroy("GeneralOverlay");
		overlay = nullptr;
	}

	void UI_Manager::init()
	{}

	void UI_Manager::update()
	{}

	void UI_Manager::cleanPanel()
	{
		for (UI_Element* elem : elements)
			delete elem;
		elements.clear();
	}
}


