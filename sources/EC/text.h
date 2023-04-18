#pragma once

#include "component.h"
#include "OgreVector3.h"

#include <string>

class UI_Text; 

class Text : public ec::Component
{
public:

	Text(std::string overlayName, std::string title, std::string fontName, std::string text,
		float x, float y, float width, float height, float r, float g, float b);
	virtual ~Text();

	virtual bool initComponent();

	virtual void render() {};

	virtual void onEnable();
	virtual void onDisable();

	virtual void start();
	virtual void update(float deltaTime);

	std::string GetName();

	void changeText(std::string newText);
	void changeFontText(std::string newFont);
	void changeSizeText(float size);
	void changeColorText(float r, float g, float b);

private:

	std::string name;

	UI_Text* text; 

	std::string textReference;
	std::string textTitle; 
	std::string fontName;
	std::string textContent;

	float posX;
	float posY;
	float tamX;
	float tamY;
	float red; 
	float green; 
	float blue;
	float screenHeight;
	float screenWidth;
};