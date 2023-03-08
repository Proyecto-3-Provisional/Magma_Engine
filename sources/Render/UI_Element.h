#pragma once

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <string>

class UI_Element
{
public:
	UI_Element(Ogre::Overlay* overReference, std::string name,
		Ogre::Real posX, Ogre::Real posY, Ogre::Real sizeX, Ogre::Real sizeY);
	~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	void setPanelPosition(double x, double y) {};
	void setPanelSize(double w, double h) {};

	std::pair<double, double> getPosition();
	std::pair<double, double> getSize();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	std::pair<double, double> position;
	std::pair<double, double> size;
	
	Ogre::OverlayManager* overlayMan_;
	Ogre::Overlay* overlay_;
	Ogre::OverlayContainer* panel;

	bool isInteractive_;
};