#include "UI_Text.h"

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <Overlay/OgreTextAreaOverlayElement.h>
#include <Overlay/OgreFontManager.h>


/******************************************************************************************************************************************************
	Crea un panel y asignamos la posicion y el tamaño del panel (en el cual se puede meter varios elementos, pero solo metemos uno)
	Luego creamos un texto y asignamos sus propios valores, incluyendo tamaño del texto y color, y lo metemos en el panel
*******************************************************************************************************************************************************/

UI_Text::UI_Text(Ogre::Overlay* overReference, string title, int posX, int posY, int sizeX, int sizeY, string fontTitle, string textContent) : UI_Element(overReference,title)
{
	position.first = posX;
	position.second = posY;

	size.first = sizeX;
	size.second = sizeY;


	Ogre::OverlayContainer* textPanel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", title));

	textPanel->setMetricsMode(Ogre::GMM_PIXELS);
	textPanel->setPosition(posX, posY);
	textPanel->setDimensions(sizeX, sizeY);

	
	Ogre::TextAreaOverlayElement* textArea = static_cast<Ogre::TextAreaOverlayElement*>(overlayMan_->createOverlayElement("TextArea", title+"Text"));

	textArea->setMetricsMode(Ogre::GMM_PIXELS);
	textArea->setPosition(posX, posY);
	textArea->setDimensions(sizeX, sizeY);

	textArea->setFontName(fontTitle);
	textArea->setCaption(textContent);

	textArea->setCharHeight(sizeY);
	textArea->setColourBottom(Ogre::ColourValue(0.3, 0.5, 0.3));
	textArea->setColourTop(Ogre::ColourValue(0.5, 0.7, 0.5));


	textPanel->addChild(textArea);
	overReference->add2D(textPanel);
}

UI_Text::~UI_Text()
{}