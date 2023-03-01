#include "UI_Image.h"

/***************************************************************************
	Crea un panel y asignamos la posicion y el tamaño del panel
	(en el cual se puede meter varios elementos, pero solo metemos uno).
	Luego le metemos la imagen como material en el panel.
***************************************************************************/

UI_Image::UI_Image(Ogre::Overlay* overReference, std::string title, std::string imageName,
	int posX, int posY, int sizeX, int sizeY) : UI_Element(overReference, title, posX, posY, sizeX, sizeY)
{
	Ogre::OverlayElement* imageUI = static_cast<Ogre::OverlayElement*>
		(overlayMan_->createOverlayElement("Panel", title + "Image"));
	imageUI->setMetricsMode(Ogre::GMM_PIXELS);
	imageUI->setPosition(posX, posY);
	imageUI->setDimensions(sizeX, sizeY);

	imageUI->setMaterialName(imageName);

	panel->addChild(imageUI);
	overReference->add2D(panel);
}

UI_Image::~UI_Image()
{}

void UI_Image::setImagePosition(float x, float y)
{
	imageUI->setPosition(x, y);
}

void UI_Image::setImageSize(float x, float y)
{
	imageUI->setDimensions(x, y);
}

void UI_Image::changeImage(std::string title ,std::string imageName)
{
	//imageUI->setMaterialName(imageName);
	panel->getChild(title)->setMaterialName(imageName);
}
