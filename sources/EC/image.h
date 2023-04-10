#pragma once

#include "component.h"

#include <string>

//#include "../Render/UI_Image.h"
//class UI_Image; 

class Image : public ec::Component
{
public:

	Image(std::string overlayName, std::string name, 
		float width, float height, float x, float y, bool interactive);

	virtual ~Image();

	std::string GetName();

	virtual void start();
	virtual void update();

	void setInteractive(bool interactive);

	void changeImage(std::string newImage);

private:

	static std::string name;
	//UI_Image* image;         

	std::string imageName;
	std::string normalName;

	bool interactive;

	float tamX;
	float tamY;
	float posX;
	float posY; 
};