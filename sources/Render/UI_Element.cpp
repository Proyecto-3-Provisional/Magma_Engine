#include "UI_Element.h"

/**************************************************************************************************************************************
	Asignamos el overlay general y su manager y creamos un panel con su posicion y tamaño al que meterle todos los elementos necesarios
***************************************************************************************************************************************/

UI_Element::UI_Element(Ogre::Overlay* overReference, std::string title,
	Ogre::Real posX, Ogre::Real posY, Ogre::Real sizeX, Ogre::Real sizeY)
{
	title_ = title;
	overlayMan_ = Ogre::OverlayManager::getSingletonPtr();
	overlay_ = overReference;
	isInteractive_ = false;

	panel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", title_));

	position.first = posX;
	position.second = posY;

	size.first = sizeX;
	size.second = sizeY;

	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(posX, posY);
	panel->setDimensions(sizeX, sizeY);

	overlay_->add2D(panel);
}

UI_Element::~UI_Element()
{
	overlay_->remove2D(panel);
	overlayMan_->destroyOverlayElement(title_);
}

// Muestra el elemento dentro del overlay
void UI_Element::showElement()
{
	panel->show();
}

// Esconde el elemento dentro del overlay
void UI_Element::hideElement()
{
	panel->hide();
}

// Comprueba si el elemento es visible o no
bool UI_Element::isElementVisible()
{
	return panel->isVisible();
}

// Devuelve la posicion del panel
std::pair<float, float> UI_Element::getPosition()
{
	return position;
}

// Devuelve el tamaño del panel
std::pair<float, float> UI_Element::getSize()
{
	return size;
}