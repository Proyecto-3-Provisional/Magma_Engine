#pragma once

#include <string>

namespace Ogre {
	class Overlay;
	class OverlayManager;
	class OverlayContainer;
	class TextAreaOverlayElement;
}

namespace magma_engine
{
	class UI_Element
	{
	public:
		UI_Element();
		virtual ~UI_Element();
		// Muestra el elemento dentro del overlay
		void showElement(); 
		// Esconde el elemento dentro del overlay
		void hideElement(); 
		// Comprueba si el elemento es visible o no
		bool isElementVisible(); 
		// Establece la posición del panel
		void setPanelPosition(float x, float y); 
		// Establece el tamaño del panel
		void setPanelSize(float w, float h); 
		// Establece la posicion del texto dentro del overlay
		void setTextPosition(float x, float y); 
		// Establece el tamaño del texto
		void setTextSize(float w, float h); 
		// Establece el material del panel
		void setMaterial(std::string nameMaterial); 

		std::pair<float, float> getPosition();
		std::pair<float, float> getSize();

		void setInteractive(bool isInteractive) {};

		bool isHidden();
		void setHide(); 

	protected:

		int nOverlay;

		std::pair<float, float> position;
		std::pair<float, float> size;

		Ogre::TextAreaOverlayElement* overlayText;
		Ogre::OverlayManager* overlayMan_;
		Ogre::Overlay* overlay_;
		Ogre::OverlayContainer* panel;

		bool isInteractive_;

		bool hidden; 

		std::string overlayReferenceName; 


		//RenderManagerContext* rend;

		/// Todos los elementos numericos (como la posicion o el tamaño), deben ser float
		/// OGRE_DOUBLE_PRECISION que se define en OgreConfig.h y ogrebuildsettings.h, si es 1 entonces puede convertir double pero no float, y si es 0 al reves
		/// Como usamos cmake, el valor de OgreConfig.h se ignora y se usa el de ogrebuildsettings.h
	};
}


