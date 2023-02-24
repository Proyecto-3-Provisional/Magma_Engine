#include "UI_Element.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

UI_Element::UI_Element(Ogre::Overlay* overReference, string title)
{
	overlayMan_ = Ogre::OverlayManager::getSingletonPtr();
	overlay_ = overReference;
	name = title;
	isInteractive_ = false;
}

UI_Element::~UI_Element() {}

void UI_Element::showElement()
{
	overlay_->show();
}

void UI_Element::hideElement()
{
	overlay_->hide();
}

bool UI_Element::isElementVisible()
{
	return overlay_->isVisible();
}

string UI_Element::getElementName()
{
	return name;
}