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