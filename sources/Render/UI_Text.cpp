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
	: UI_Element(overReference,title, posX, posY, sizeX, sizeY)
{	
	textArea = static_cast<Ogre::TextAreaOverlayElement*>
		(overlayMan_->createOverlayElement("TextArea", title+"Text"));

	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(posX, posY);
	textArea->setDimensions(sizeX, sizeY);

	textArea->setFontName(fontTitle);
	textArea->setCaption(textContent);

	textArea->setCharHeight(sizeY);
	textArea->setColourBottom(Ogre::ColourValue(r, g, b));
	textArea->setColourTop(Ogre::ColourValue(r, g, b));

	panel->addChild(textArea);
	overReference->add2D(panel);
}

UI_Text::~UI_Text()
{
	delete textArea;
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
