#include <render/ui_text.h>

/***************************************************************************
	Crea un panel y asignamos la posicion y el tama�o del panel
	(en el cual se puede meter varios elementos, pero solo metemos uno).
	Luego creamos un texto y asignamos sus propios valores, incluyendo
	tama�o del texto y color, y lo metemos en el panel.
***************************************************************************/

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

//Metodo para cambiar la fuente del texto
void UI_Text::setFont(std::string font)
{
	overlayText->setFontName(font); 
}

//Metodo para cambiar el contenido del texto
void UI_Text::setText(std::string text)
{
	overlayText->setCaption(text);
}

//Metodo para cambiar el tama�o del texto
void UI_Text::setFontSize(float fontSize)
{
	overlayText->setCharHeight(fontSize);
}

//Metodo para cambiar el color del texto
void UI_Text::setTextColor(float r, float g, float b)
{
	overlayText->setColourBottom(Ogre::ColourValue(r, g, b));
	overlayText->setColourTop(Ogre::ColourValue(r, g, b));
}
