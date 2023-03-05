#include "ui_button.h"

UIButton::UIButton(Ogre::Overlay* overReference, std::string title, std::string imageName, std::string hoverImageName, std::string pressedImageName,
	int posX, int posY, int sizeX, int sizeY) : UI_Element(overReference, title, posX, posY, sizeX, sizeY)
{
	buttonImage = static_cast<Ogre::OverlayElement*>
		(overlayMan_->createOverlayElement("Panel", title + "Image"));
	buttonImage->setMetricsMode(Ogre::GMM_PIXELS);
	//buttonImage->setPosition(posX, posY);
	buttonImage->setDimensions(sizeX, sizeY);

	buttonImage->setMaterialName(imageName);

	hoverButtonName = hoverImageName; 
	pressedButtonName = pressedImageName; 
	normalButtonName = imageName; 

	x = posX; 
	y = posY; 

	tamX = sizeX; 
	tamY = sizeY; 

	pressed = false; 
	onButton = false; 

	panel->addChild(buttonImage);
	overReference->add2D(panel);
}

UIButton::~UIButton() {}

void UIButton::setButtonPosition(float x, float y)
{
	buttonImage->setPosition(x, y);
}

void UIButton::setButtonSize(float x, float y)
{
	buttonImage->setDimensions(x, y);
}

void UIButton::cursorOnButton()
{
	onButton = true; 
	buttonImage->setMaterialName(hoverButtonName);
}

void UIButton::mousePressedButton()
{
	pressed = true; 
	buttonImage->setMaterialName(pressedButtonName);
}

void UIButton::mouseLeavingButton()
{
	if (!pressed)
		buttonImage->setMaterialName(normalButtonName);

	onButton = false; 
}

bool UIButton::isButtonPressed()
{
	return pressed; 
}

bool UIButton::isOnButton()
{
	return onButton;
}

bool UIButton::isCursorInsideBounds(int mouseX, int mouseY)
{
	return (mouseX > x && mouseX < (x + tamX)) && (mouseY > y && mouseY < (y + tamY)); 
}
