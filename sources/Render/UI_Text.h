#pragma once

#include "UI_Element.h"

namespace Ogre
{
	class TextAreaOverlayElement;
}

class UI_Text : public UI_Element
{
public:

	UI_Text(Ogre::Overlay* overReference, std::string title, Ogre::Real posX, Ogre::Real posY,
		Ogre::Real sizeX, Ogre::Real sizeY, std::string fontTitle, std::string textContent,
		float r, float g, float b);
	~UI_Text();

	void setText(std::string newText);
	void setTextPosition(double x, double y);
	void setTextSize(double x, double y);
	void changeFontSize(int fontSize);
	void changeTextColor(float r, float g, float b);

private:
	Ogre::TextAreaOverlayElement* textArea;
};
