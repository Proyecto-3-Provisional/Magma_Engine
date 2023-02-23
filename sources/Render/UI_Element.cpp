#include "UI_Element.h"
#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

UIElement::UIElement(pair<float, float> pos, pair<float, float> size)
{
	ui_object->setMetricsMode(Ogre::GMM_PIXELS);
	ui_object->setPosition(pos.first, pos.second);
	ui_object->setDimensions(size.first, size.second);

}

UIElement::~UIElement()
{

}