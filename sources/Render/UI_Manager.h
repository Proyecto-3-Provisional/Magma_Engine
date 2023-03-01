#pragma once

#include <memory>
#include <string>
#include <vector>

//#include "UI_Image.h" //borrar si esta mal (esta puesto para que main pueda acceder a metodos de UI_image pero esta mal

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
	
	void createImage(std::string imagePanelName, std::string imageName, int posX, int posY,
		int sizeX, int sizeY);

	// Crea un UI_Element de X tipo(Texto, image...) con su nombre de panel, una referencia al overlay y los argumentos que necesite su tipo
	template<typename T, typename ...Ts>
	T* createElement(std::string panelName, Ts&&... args)
	{
		T* elem = new T(overlay, panelName, args...);
		elements.push_back(elem);
		return elem;
	}

private:
	Ogre::OverlayManager* overlayMngr_;
	Ogre::Overlay* overlay;
	std::vector<UI_Element*> elements;
};