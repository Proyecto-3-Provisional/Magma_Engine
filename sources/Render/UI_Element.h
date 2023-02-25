#pragma once

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <string>

class UI_Element
{
public:
	UI_Element(Ogre::Overlay* overReference, std::string name,
		int posX, int posY, int sizeX, int sizeY);
	~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	void setPanelPosition(float x, float y) {};
	void setPanelSize(float w, float h) {};

	std::pair<float, float> getPosition();
	std::pair<float, float> getSize();

	std::string getElementName();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	std::pair<float, float> position;
	std::pair<float, float> size;
	
	Ogre::OverlayManager* overlayMan_;
	Ogre::Overlay* overlay_;
	Ogre::OverlayContainer* panel;

	std::string name;
	bool isInteractive_;
};