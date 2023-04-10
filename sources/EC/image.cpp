#include "image.h"

Image::Image(std::string overlayName, std::string name, 
	float width, float height, float x, float y, bool interact) : Component() 
{
	imageName = overlayName;
	normalName = name;

	tamX = width;
	tamY = height;

	posX = x; 
	posY = y; 

	interactive = interact;
}

Image::~Image() {}

std::string Image::GetName()
{
	return imageName; 
}

void Image::start()
{
	/*image->setPanelSize(tamX, tamY); 
	image->setPanelPosition(posX, posY); 
	image->setInteractive(interactive);*/
}

void Image::update() {}

void Image::setInteractive(bool interact)
{
	interactive = interact;
}

void Image::changeImage(std::string newImage)
{
	//image->setMaterial(newImage); 
}