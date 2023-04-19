#include <EC/Button.h>


Button::Button(std::string overlayName, std::string imageName,
	std::string hoverImageName, std::string pressedImageName,
	float width, float height, float x, float y) : Component()
{
	buttonName = overlayName;
	normalButtonName = imageName;
	hoverButtonName = hoverImageName;
	pressedButtonName = pressedImageName;

	tamX = width;
	tamY = height;
	posX = x;
	posY = y;

	//input = Singleton<InputManager>::instance();
}

Button::~Button() {};

std::string Button::GetName()
{
	return buttonName;
}

void Button::start()
{
	/*button->setPanelPosition(posX, posY);
	button->setPanelSize(tamX, tamY);
	button->setInteractive(true);*/
}

void Button::update()
{
	pressed = false;

	/*auto pointPos = input->getMousePos();

	if (button->isCursorInsideBounds(pointPos.first, pointPos.second))
	{
		if (input->isMouseDown())
		{
			pressed = true;
			button->setMaterial(pressedButtonName);
		}

		else
			button->setMaterial(hoverButtonName);
	}

	else
		button->setMaterial(normalButtonName);*/
}