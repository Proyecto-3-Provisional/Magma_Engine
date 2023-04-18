#include "UI_Text.h"
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>

/***************************************************************************
	Crea un panel y asignamos la posicion y el tamaño del panel
	(en el cual se puede meter varios elementos, pero solo metemos uno).
	Luego creamos un texto y asignamos sus propios valores, incluyendo
	tamaño del texto y color, y lo metemos en el panel.
***************************************************************************/

UI_Text::UI_Text(Ogre::Overlay* overReference, std::string title,
	float posX, float posY, float sizeX, float sizeY, std::string fontTitle,
	std::string textContent, float r, float g, float b)
	: UI_Element()
{	
	textArea = static_cast<Ogre::TextAreaOverlayElement*>
		(overlayMan_->createOverlayElement("TextArea", title_ + "Text"));

	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(posX, posY);
	textArea->setDimensions(sizeX, sizeY);

	textArea->setFontName(fontTitle);
	textArea->setCaption(textContent);

	textArea->setCharHeight(sizeY);
	textArea->setColourBottom(Ogre::ColourValue(r, g, b));
	textArea->setColourTop(Ogre::ColourValue(r, g, b));

	panel->addChild(textArea);

	screenwidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	screenheight = (float)Singleton<RenderManager>::instance()->getWinHeight();
	originalwidth = sizeX;
	originalheight = sizeY;
	originalposx = posX;
	originalposy = posY;
}

UI_Text::~UI_Text()
{
	panel->removeChild(title_ + "Text");
	overlayMan_->destroyOverlayElement(textArea);
}

void UI_Text::setText(std::string newText)
{
	textArea->setCaption(newText);
}

void UI_Text::setTextPosition(float x, float y)
{
	textArea->setPosition(x, y);
}

void UI_Text::setTextSize(float x, float y)
{
	textArea->setDimensions(x, y);
}

void UI_Text::changeFontSize(float fontSize)
{
	textArea->setCharHeight(fontSize);
}

void UI_Text::changeTextColor(float r, float g, float b)
{
	textArea->setColourBottom(Ogre::ColourValue(r, g, b));
	textArea->setColourTop(Ogre::ColourValue(r, g, b));
}

void UI_Text::updateText() {
	float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
	if (newWidth != 0 && newHeight != 0 && screenwidth != 0 && screenheight != 0) {
		textArea->setPosition(originalposx * (newWidth / screenwidth), originalposy * (newHeight / screenheight));
		textArea->setDimensions(originalwidth * (newWidth / screenwidth), originalheight * (newHeight / screenheight));
		textArea->setCharHeight(originalheight * (newHeight / screenheight));
	}
}