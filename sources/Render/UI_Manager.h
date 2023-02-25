#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Ogre
{
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

class UI_Element;

class UI_Manager
{
public:
	UI_Manager();
	~UI_Manager();

	void init();
	void update();
	void cleanPanel();
	
	void createText(std::string textPanelName, int posX, int posY,
		int sizeX, int sizeY, std::string fontName, std::string textContent,
		float colorX, float colorY, float colorZ);

	UI_Element* getElement(std::string name);

private:
	Ogre::OverlayManager* overlayMngr_;
	Ogre::Overlay* overlay;
	std::vector<UI_Element*> elements;
};