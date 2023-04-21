#include <Render/ui_element.h>

namespace magma_engine
{
	UI_Element::UI_Element()
	{
		overlayMan_ = Ogre::OverlayManager::getSingletonPtr();

		isInteractive_ = false;

		nOverlay++;
	}

	UI_Element::~UI_Element()
	{
		overlayMan_->destroy(overlay_);
	}

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

	void UI_Element::setMaterial(std::string materialName)
	{
		panel->setMaterialName(materialName);
	}

	void UI_Element::setPanelPosition(float x, float y)
	{
		position.first = x;
		position.second = y;

		panel->setPosition(x, y);
	}

	void UI_Element::setPanelSize(float w, float h)
	{
		size.first = w;
		size.second = h;

		panel->setDimensions(w, h);
	}

	void UI_Element::setTextPosition(float x, float y)
	{
		position.first = x;
		position.second = y;

		overlayText->setPosition(x, y);
	}

	void UI_Element::setTextSize(float w, float h)
	{
		size.first = w;
		size.second = h;

		overlayText->setDimensions(w, h);
	}

	std::pair<float, float> UI_Element::getPosition()
	{
		return position;
	}

	std::pair<float, float> UI_Element::getSize()
	{
		return size;
	}
}

