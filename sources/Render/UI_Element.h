#pragma once

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <string>

#include "render_manager.h"


class UI_Element
{
public:
	UI_Element(Ogre::Overlay* overReference, std::string name,
		Ogre::Real posX, Ogre::Real posY, Ogre::Real sizeX, Ogre::Real sizeY);
	virtual ~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	void setPanelPosition(float x, float y) {};
	void setPanelSize(float w, float h) {};

	std::pair<float, float> getPosition();
	std::pair<float, float> getSize();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	std::pair<float, float> position;
	std::pair<float, float> size;
	
	Ogre::OverlayManager* overlayMan_;
	Ogre::Overlay* overlay_;
	Ogre::OverlayContainer* panel;

	bool isInteractive_;

	Ogre::String title_;

	//RenderManagerContext* rend;

	/// Todos los elementos numericos (como la posicion o el tamaño), deben ser float
	/// OGRE_DOUBLE_PRECISION que se define en OgreConfig.h y ogrebuildsettings.h, si es 1 entonces puede convertir double pero no float, y si es 0 al reves
	/// Como usamos cmake, el valor de OgreConfig.h se ignora y se usa el de ogrebuildsettings.h
};