#include <Render/ui_image.h>

UI_Image::UI_Image(std::string overReference, std::string imageName,
	float posX, float posY, float sizeX, float sizeY) : UI_Element()
{
	panel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", overReference + std::to_string(nOverlay)));
	panel->setMetricsMode(Ogre::GMM_PIXELS);
	panel->setPosition(posX, posY);
	panel->setDimensions(sizeX, sizeY);

	panel->setMaterialName(imageName);

	overlay_ = overlayMan_->create(overReference + std::to_string(nOverlay));
	overlay_->add2D((Ogre::OverlayContainer*)panel);
	overlay_->show();
}

UI_Image::~UI_Image() = default; 