#include "UI_Element.h"

/**************************************************************************************************************************************
	Asignamos el overlay general y su manager y creamos un panel con su posicion y tamaño al que meterle todos los elementos necesarios
***************************************************************************************************************************************/

UI_Element::UI_Element(Ogre::Overlay* overReference, string title, int posX, int posY, int sizeX, int sizeY)
{
	overlayMan_ = Ogre::OverlayManager::getSingletonPtr();
	overlay_ = overReference;
	name = title;
	isInteractive_ = false;

	panel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", title));

	position.first = posX;
	position.second = posY;

	size.first = sizeX;
	size.second = sizeY;

	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(posX, posY);
	panel->setDimensions(sizeX, sizeY);
}

UI_Element::~UI_Element() {}

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

// Devuelve el nombre del elemento
string UI_Element::getElementName()
{
	return name;
}

// Devuelve la posicion del panel
pair<float, float> UI_Element::getPosition()
{
	return position;
}

// Devuelve el tamaño del panel
pair<float, float> UI_Element::getSize()
{
	return size;
}