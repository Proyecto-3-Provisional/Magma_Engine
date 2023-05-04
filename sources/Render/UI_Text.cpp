#include <render/ui_text.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>

namespace magma_engine
{
	UI_Text::UI_Text(std::string overlayName, std::string title,
		float posX, float posY, float sizeX, float sizeY)
		: UI_Element()
	{
		overlayReferenceName = overlayName + std::to_string(nOverlay);

		overlayText = static_cast<Ogre::TextAreaOverlayElement*>
			(overlayMan_->createOverlayElement("TextArea", overlayReferenceName + "Text"));

		panel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", overlayReferenceName));

		overlayText->setMetricsMode(Ogre::GMM_PIXELS);
		overlayText->setPosition(posX, posY);
		overlayText->setDimensions(sizeX, sizeY);

		panel->addChild(overlayText);

		overlay_ = overlayMan_->create(overlayName + std::to_string(nOverlay));
		overlay_->add2D((Ogre::OverlayContainer*)panel);
		overlay_->show();
	}

	UI_Text::~UI_Text() 
	{
		overlayMan_->destroyOverlayElement(overlayReferenceName);
	}

	void UI_Text::setFont(std::string font)
	{
		overlayText->setFontName(font);
	}

	void UI_Text::setText(std::string text)
	{
		overlayText->setCaption(text);
	}

	void UI_Text::setFontSize(float fontSize)
	{
		overlayText->setCharHeight(fontSize);
	}

	void UI_Text::setTextColor(float r, float g, float b)
	{
		overlayText->setColourBottom(Ogre::ColourValue(r, g, b));
		overlayText->setColourTop(Ogre::ColourValue(r, g, b));
	}
}

