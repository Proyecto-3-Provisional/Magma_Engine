#include "UI_Image.h"

/***************************************************************************
	Crea un panel y asignamos la posicion y el tamaño del panel
	(en el cual se puede meter varios elementos, pero solo metemos uno).
	Luego le metemos la imagen como material en el panel.
***************************************************************************/

UI_Image::UI_Image(Ogre::Overlay* overReference, std::string title, std::string imageName,
	float posX, float posY, float sizeX, float sizeY) : UI_Element(overReference, title, posX, posY, sizeX, sizeY)
{
	imageUI = overlayMan_->createOverlayElement("Panel", title_ + "Image");
	imageUI->setMetricsMode(Ogre::GMM_PIXELS);
	imageUI->setPosition(posX, posY);
	imageUI->setDimensions(sizeX, sizeY);

	imageUI->setMaterialName(imageName);

	panel->addChild(imageUI);
	
	screenwidth = Singleton<RenderManager>::instance()->getWinWidth();
	screenheight = Singleton<RenderManager>::instance()->getWinHeight();
	originalwidth = sizeX;
	originalheight = sizeY;
	originalposx = posX;
	originalposy = posY;
}

UI_Image::~UI_Image()
{
	panel->removeChild(title_ + "Image");
	overlayMan_->destroyOverlayElement(imageUI);
}

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
	panel->getChild(title)->setMaterialName(imageName);
}

void UI_Image::updateImage() {
	float newWidth = Singleton<RenderManager>::instance()->getWinWidth();
	float newHeight = Singleton<RenderManager>::instance()->getWinHeight();
	if (newWidth != 0 && newHeight != 0 && screenwidth != 0 && screenheight != 0) {
		imageUI->setPosition(originalposx * (newWidth / screenwidth), originalposy * (newHeight / screenheight));
		imageUI->setDimensions(originalwidth * (newWidth / screenwidth), originalheight * (newHeight / screenheight));
	}
}