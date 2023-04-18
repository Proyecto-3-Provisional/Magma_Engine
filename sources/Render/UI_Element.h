#pragma once

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <string>

#include "render_manager.h"


class UI_Element
{
public:
	UI_Element();
	virtual ~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	void setPanelPosition(float x, float y);
	void setPanelSize(float w, float h);
	void setMaterial(std::string nameMaterial); 

	std::pair<float, float> getPosition();
	std::pair<float, float> getSize();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	int nOverlay; 

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