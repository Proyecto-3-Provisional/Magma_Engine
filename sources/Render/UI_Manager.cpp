#include <Render/ui_manager.h>
#include <Render/ui_element.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <iostream>

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

	void UI_Manager::deleteElement(UI_Element* f)
	{
		auto it = elements.begin(); 
		bool found = false;

		while (it != elements.end() && !found)
		{
			if ((*it) == f)
			{
				delete f; 

				it = elements.erase(it); 
				found = true;
			}

			else it++; 
		}

		if (!found)
			std::cout << "No eliminado\n";
	}

	void UI_Manager::update() 
	{
		//for (UI_Element* elem : elements)
		//{
		//	//if (elem->isHidden() && elem->isElementVisible())
		//	//	elem->hideElement();
		//	//else if (!elem->isHidden() && !elem->isElementVisible())
		//	//	elem->showElement(); 
		//}
			
	}

	void UI_Manager::flush()
	{
		for (UI_Element* elem : elements)
			elem->setHide(); 
	}

	void UI_Manager::cleanPanel()
	{
		for (UI_Element* elem : elements)
			delete elem;
		elements.clear();
	}
}


