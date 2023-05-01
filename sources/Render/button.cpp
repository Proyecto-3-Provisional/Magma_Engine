#include <iostream>
#include <Render/Button.h>
#include<Render/ui_button.h>
#include<Render/UI_Manager.h>
#include<Input/input_manager.h>

namespace magma_engine
{
	Button::Button() : Component(), buttonName(), normalButtonName(), hoverButtonName(), pressedButtonName(), tamX(), tamY(), posX(), posY()
	{

	}

	Button::~Button() {};

	std::string Button::GetName()
	{
		return buttonName;
	}

	bool Button::start()
	{
		button = Singleton<UI_Manager>::instance()->createElement<UIButton>(buttonName, normalButtonName, hoverButtonName,
			pressedButtonName, posX, posY, tamX, tamY);

		button->setPanelPosition(posX, posY);
		button->setPanelSize(tamX, tamY);
		button->setInteractive(true);
		return true;
	}

	bool Button::initComponent(std::map<std::string, std::string> args)
	{
		try
		{
			buttonName = args["overlayName"];
			normalButtonName = args["imageName"];
			hoverButtonName = args["hoverImageName"];
			pressedButtonName = args["pressedImageName"];

			tamX = stof(args["width"]);
			tamY = stof(args["height"]);
			posX = stof(args["x"]);
			posY = stof(args["y"]);
			screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
			screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
			pressed = false;
		}
		catch (std::exception e)
		{
			std::cout << "Button Component : " << e.what();
			return false;
		}
		
		return true;
	}

	bool Button::isCursorInsideBounds(int mouseX, int mouseY)
	{
		return (mouseX > posX && mouseX < (posX + tamX)) && (mouseY > posY && mouseY < (posY + tamY));
	}

	void Button::update(float deltaTime)
	{
		auto pointPos = Singleton<InputManager>::instance()->getMousePos();

		if (isCursorInsideBounds(pointPos.first, pointPos.second))
		{
			if (Singleton<InputManager>::instance()->isMouseDown())
			{
				pressed = true;
				button->setMaterial(pressedButtonName);
			}

			else
			{
				if (!pressed)
					button->setMaterial(hoverButtonName);
			}
		}
		else
		{
			button->setMaterial(normalButtonName);
			pressed = false;
		}

		float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
		float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();

		if (newWidth != 0 && newHeight != 0 && screenWidth != 0 && screenHeight != 0)
		{
			button->setPanelPosition(posX * (newWidth / screenWidth), posY * (newHeight / screenHeight));
			button->setPanelSize(tamX * (newWidth / screenWidth), tamY * (newHeight / screenHeight));
		}
	}

	void Button::onEnable()
	{
		if (button != nullptr)
			button->showElement();
	}

	void Button::onDisable()
	{
		button->hideElement();
	}

	void Button::setInteractive(bool interact)
	{
		interactive = interact;
	}

	bool Button::isButtonPressed() {
		return pressed;
	}
}

