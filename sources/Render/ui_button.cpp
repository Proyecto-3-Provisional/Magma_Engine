#include <Render/ui_button.h>

UIButton::UIButton(Ogre::Overlay* overReference, std::string title, std::string imageName, std::string hoverImageName, std::string pressedImageName,
	float posX, float posY, float sizeX, float sizeY) : UI_Element()
{
	buttonImage = overlayMan_->createOverlayElement("Panel", title_ + "Image");
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

	screenwidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	screenheight = (float)Singleton<RenderManager>::instance()->getWinHeight();
	originalPosX = posX;
	originalPosY = posY;
	originalTamX = sizeX;
	originalTamY = sizeY;
}

UIButton::~UIButton() 
{
	panel->removeChild(title_ + "Image");
	overlayMan_->destroyOverlayElement(buttonImage);
}

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

void UIButton::updateButton() {

	float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
	if (newWidth != 0 && newHeight != 0 && screenwidth != 0 && screenheight != 0) {
		x = originalPosX * (newWidth / screenwidth);
		y = originalPosY * (newHeight / screenheight);
		buttonImage->setPosition(x, y);

		tamX = originalTamX * (newWidth / screenwidth);
		tamY = originalTamY * (newHeight / screenheight);
		buttonImage->setDimensions(tamX, tamY);
	}
}