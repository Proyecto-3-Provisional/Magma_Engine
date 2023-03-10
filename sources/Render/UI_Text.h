#pragma once

#include "UI_Element.h"

namespace Ogre
{
	class TextAreaOverlayElement;
}

class UI_Text : public UI_Element
{
public:

	UI_Text(Ogre::Overlay* overReference, std::string title, float posX, float posY,
		float sizeX, float sizeY, std::string fontTitle, std::string textContent,
		float r, float g, float b);
	~UI_Text();

	void setText(std::string newText);
	void setTextPosition(float x, float y);
	void setTextSize(float x, float y);
	void changeFontSize(float fontSize);
	void changeTextColor(float r, float g, float b);

private:
	Ogre::TextAreaOverlayElement* textArea;
};
