#pragma once

#include <EC/component.h>

#include <string>

class UI_Image; 

class Image : public ec::Component
{
public:

	Image(); 
	Image(std::string overlayName, std::string name,
		float width, float height, float x, float y);

	virtual ~Image();

	virtual bool initComponent();

	virtual void render() {};

	virtual void onEnable();
	virtual void onDisable();

	virtual void start();
	virtual void update(float deltaTime);

	std::string GetName();

	void setInteractive(bool interactive);

	void changeImage(std::string newImage);

private:

	static std::string name;
	UI_Image* image;         

	std::string imageName;
	std::string normalName;

	bool interactive;

	float tamX;
	float tamY;
	float posX;
	float posY; 
	float screenHeight; 
	float screenWidth; 
};