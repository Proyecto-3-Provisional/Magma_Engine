#pragma once

#include "component.h"
#include "OgreVector3.h"

#include <string>

class UI_Text; 

class Text : public ec::Component
{
public:

	Text(std::string overlayName, std::string fontName, std::string text,
		float x, float y, float width, float height);
	virtual ~Text();

	std::string GetName();

	virtual void start();
	virtual void update();

	void changeText(std::string newText);

private:

	std::string name;

	UI_Text* text; 

	std::string textName;
	std::string fontName;
	std::string textContent;

	float posX;
	float posY;
	float tamX;
	float tamY;
};