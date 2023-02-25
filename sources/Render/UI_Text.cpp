#include "UI_Text.h"
#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>


/******************************************************************************************************************************************************
	Crea un panel y asignamos la posicion y el tama�o del panel (en el cual se puede meter varios elementos, pero solo metemos uno)
	Luego creamos un texto y asignamos sus propios valores, incluyendo tama�o del texto y color, y lo metemos en el panel
*******************************************************************************************************************************************************/

UI_Text::UI_Text(Ogre::Overlay* overReference, string title, int posX, int posY, int sizeX, int sizeY, string fontTitle, string textContent, Ogre::ColourValue textColor) : UI_Element(overReference,title, posX, posY, sizeX, sizeY)
{	
	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayMan_->createOverlayElement("TextArea", title+"Text"));

	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(posX, posY);
	textArea->setDimensions(sizeX, sizeY);

	textArea->setFontName(fontTitle);
	textArea->setCaption(textContent);

	textArea->setCharHeight(sizeY);
	textArea->setColourBottom(textColor);
	textArea->setColourTop(textColor);


	panel->addChild(textArea);
	overReference->add2D(panel);
}

UI_Text::~UI_Text() {}

void UI_Text::setTextPosition(float x, float y)
{
	textArea->setPosition(x, y);
}

void UI_Text::setTextSize(float x, float y)
{
	textArea->setDimensions(x, y);
}

void UI_Text::changeFontSize(int fontSize)
{
	textArea->setCharHeight(fontSize);
}

void UI_Text::changeTextColor(Ogre::ColourValue newColor)
{
	textArea->setColourBottom(newColor);
	textArea->setColourTop(newColor);
}