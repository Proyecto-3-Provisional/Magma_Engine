#include <iostream>
#include <Render/render_manager.h>
#include <Render/image.h>
#include <Render/UI_Image.h>
#include <Render/UI_Manager.h>

namespace magma_engine
{
	Image::Image() : Component(), imageName(), normalName(), tamX(), tamY(), posX(), posY()
	{
	}

	Image::~Image()
	{
		Singleton<UI_Manager>::instance()->deleteElement(image);
	}

	std::string Image::GetName()
	{
		return imageName;
	}


	bool Image::initComponent(std::map<std::string, std::string> args)
	{
		try
		{
			imageName = args["overlayName"];
			normalName = args["name"];

			tamX = stof(args["width"]);
			tamY = stof(args["height"]);

			posX = stof(args["x"]);
			posY = stof(args["y"]);

			screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
			screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
		}
		catch (std::exception e)
		{
			std::cout << "WARNING!- error en un componente Image : \n\n     " << e.what();
			return false;
		}

		return true;
	}

	bool Image::start()
	{
		image = Singleton<UI_Manager>::instance()->createElement<UI_Image>(
				imageName, normalName, posX, posY, tamX, tamY);

		if (image == nullptr)
		{
			std::cout << "WARNING!- error al cargar Image  \n\n";
			return false;
		}

		image->setPanelPosition(posX, posY);
		image->setPanelSize(tamX, tamY);
		image->setInteractive(interactive);
		
		return true;
	}

	void Image::onEnable()
	{
		if (image != nullptr)
			image->showElement();
	}

	void Image::onDisable()
	{
		image->hideElement();
	}

	void Image::update(float deltaTime)
	{
		float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
		float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();

		if (newWidth != 0 && newHeight != 0 && screenWidth != 0 && screenHeight != 0)
		{
			image->setPanelPosition(posX * (newWidth / screenWidth), posY * (newHeight / screenHeight));
			image->setPanelSize(tamX * (newWidth / screenWidth), tamY * (newHeight / screenHeight));
		}
	}

	void Image::setInteractive(bool interact)
	{
		interactive = interact;
	}

	void Image::changeImage(std::string newImage)
	{
		image->setMaterial(newImage);
	}
}
