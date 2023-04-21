#include <render/ui_text.h>

UI_Text::UI_Text(std::string overlayName, std::string title,
	float posX, float posY, float sizeX, float sizeY)
	: UI_Element()
{	
	overlayText = static_cast<Ogre::TextAreaOverlayElement*>
		(overlayMan_->createOverlayElement("TextArea", overlayName + "Text"));

	overlayText->setMetricsMode(Ogre::GMM_PIXELS);
	overlayText->setPosition(posX, posY);
	overlayText->setDimensions(sizeX, sizeY);

	overlay_ = overlayMan_->create(overlayName + std::to_string(nOverlay));
	overlay_->add2D((Ogre::OverlayContainer*)overlayText);
	overlay_->show();
}

UI_Text::~UI_Text() = default; 

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
