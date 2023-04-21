#include <EC/image.h>

#include <Render/UI_Image.h>
#include <Render/UI_Manager.h>

Image::Image(std::string overlayName, std::string name,
	float width, float height, float x, float y) : Component() 
{
	imageName = overlayName;
	normalName = name;

	tamX = width;
	tamY = height;

	posX = x;
	posY = y;

	screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
}

Image::~Image() {}

std::string Image::GetName()
{
	return imageName; 
}

bool Image::initComponent() { return true; }

void Image::start()
{
	image = Singleton<UI_Manager>::instance()->createElement<UI_Image>(imageName, normalName, posX, posY, tamX, tamY);

	image->setPanelPosition(posX, posY);
	image->setPanelSize(tamX, tamY); 
	image->setInteractive(interactive);
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