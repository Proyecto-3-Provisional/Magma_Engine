#pragma once
#include "UI_Element.h"

namespace Ogre {
	class TextAreaOverlayElement;
}

class UI_Text : public UIElement
{
public:
	UI_Text(string fontTitle, string textContent, int fontSize);
	~UI_Text();

	void setPosition();
	void setSize();

	void setWidth();
	void setHeight();

	void changeFontSize(int fontSize);
	virtual pair<float, float> getPosition();
	virtual pair<float, float> getSize();

private:
	Ogre::TextAreaOverlayElement* textArea;

};

