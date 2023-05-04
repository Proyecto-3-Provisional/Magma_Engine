#include <Render/ui_button.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

namespace magma_engine
{
	UIButton::UIButton(std::string overReference, std::string imageName, std::string hoverImageName, std::string pressedImageName,
		float posX, float posY, float sizeX, float sizeY) : UI_Element()
	{
		overlayReferenceName = overReference + std::to_string(nOverlay);
		panel = static_cast<Ogre::OverlayContainer*>(overlayMan_->createOverlayElement("Panel", overlayReferenceName));

		panel->setMetricsMode(Ogre::GMM_PIXELS);
		panel->setPosition(posX, posY);
		panel->setDimensions(sizeX, sizeY);

		panel->setMaterialName(imageName);

		overlay_ = overlayMan_->create(overReference + std::to_string(nOverlay));
		overlay_->add2D((Ogre::OverlayContainer*)panel);
		overlay_->show();

	}

	UIButton::~UIButton()
	{
		overlayMan_->destroyOverlayElement(overlayReferenceName);
	}
}


