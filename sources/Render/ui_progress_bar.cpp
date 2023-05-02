#include <Render/ui_progress_bar.h>

#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>
#include <Overlay/OgreTextAreaOverlayElement.h>

namespace magma_engine
{
	UI_Progress_Bar::UI_Progress_Bar(std::string overReference, std::string imageName,
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

	UI_Progress_Bar::~UI_Progress_Bar() = default;
}