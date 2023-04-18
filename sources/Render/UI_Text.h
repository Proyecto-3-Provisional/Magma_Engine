#pragma once

#include "UI_Element.h"

class UI_Text : public UI_Element
{
public:

	UI_Text(std::string overlayName, std::string title,
		float posX, float posY, float sizeX, float sizeY);
	~UI_Text();

	void setFont(std::string font); 
	void setText(std::string text);
	void setFontSize(float fontSize);
	void setTextColor(float r, float g, float b);
};
