#include <iostream>

#include <Render/ui_button.h>
#include <Render/Button.h>
#include <Render/UI_Manager.h>

#include <Input/input_manager.h>

#include <EC/scene_manager.h>
#include <EC/scene.h>

#include <Lua/scene_loader.h>

#include <Sounds/sound_manager.h>

namespace magma_engine
{
	ButtonType convert(const std::string& str)
	{
		if (str == "NEXT_SCENE")
			return NEXT_SCENE;
		else if (str == "BACK_SCENE")
			return BACK_SCENE;
		else if (str == "CHANGE_SCENE")
			return CHANGE_SCENE;
		else if (str == "MORE_VOLUME")
			return MORE_VOLUME;
		else if (str == "LESS_VOLUME")
			return LESS_VOLUME;
		else if (str == "LETTER")
			return LETTER;
		else
			return QUIT; 
	}

	Button::Button() : Component(), buttonName(), normalButtonName(), hoverButtonName(), pressedButtonName(), tamX(), tamY(), posX(), posY()
	{
	}

	Button::~Button() 
	{
		Singleton<UI_Manager>::instance()->deleteElement(button);
	};

	void Button::render() {}

	std::string Button::GetName()
	{
		return buttonName;
	}

	bool Button::start()
	{
		button = Singleton<UI_Manager>::instance()->createElement<UIButton>(
			buttonName, normalButtonName, hoverButtonName,
			pressedButtonName, posX, posY, tamX, tamY);

		if (button == nullptr)
		{
			std::cout << "WARNING! - error al cargar button \n\n";
			return false;
		}

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

			typeButton = convert(args["buttonType"]);

			sceneRoute = args["sceneRoute"]; 

			tamX = stof(args["width"]);
			tamY = stof(args["height"]);
			posX = stof(args["x"]);
			posY = stof(args["y"]);

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

				switch (typeButton)
				{
				case NEXT_SCENE: 

					Singleton<magma_engine::UI_Manager>::instance()->flush();

					sceneRead = Singleton<magma_engine::SceneLoader>::instance()->loadScene(sceneRoute);

					if (sceneRead >= 0)
					{
						SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile();

						Scene* scn = new magma_engine::Scene();

						bool sceneCreated = scn->loadScene(sncMp);

						if (sceneCreated)
							Singleton<magma_engine::SceneManager>::instance()->pushScene(scn);
					}
					break;
				case BACK_SCENE:

					Singleton<magma_engine::SceneManager>::instance()->popScene();

					Singleton<magma_engine::UI_Manager>::instance()->flush();
					break;
				case CHANGE_SCENE:

					Singleton<magma_engine::UI_Manager>::instance()->flush();

					sceneRead = Singleton<magma_engine::SceneLoader>::instance()->loadScene(sceneRoute);

					if (sceneRead >= 0)
					{
						SceneMap* sncMp = Singleton<magma_engine::SceneLoader>::instance()->getMapFile();

						Scene* scn = new magma_engine::Scene();

						bool sceneCreated = scn->loadScene(sncMp);

						if (sceneCreated)
							Singleton<magma_engine::SceneManager>::instance()->changeScene(scn);
					}
					break;
				case MORE_VOLUME: 
					sound = Singleton<magma_engine::SoundManager>::instance()->getVolume(); 
					Singleton<magma_engine::SoundManager>::instance()->setVolume(sound + 0.1f);
					Singleton<magma_engine::SoundManager>::instance()->setVolumeSongs();
					break; 
				case LESS_VOLUME:
					sound = Singleton<magma_engine::SoundManager>::instance()->getVolume();
					Singleton<magma_engine::SoundManager>::instance()->setVolume(sound - 0.1f);
					Singleton<magma_engine::SoundManager>::instance()->setVolumeSongs(); 
					break;
				case QUIT:
					Singleton<InputManager>::instance()->exitPetition(); 
					break;
				default: 
					break; 
				}
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

	bool Button::isButtonPressed() 
	{
		return pressed;
	}

	std::string Button::getSceneRoute()
	{
		return sceneRoute; 
	}
}

