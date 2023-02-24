#pragma once
#include "UI_Element.h"

namespace Ogre {
	class TextAreaOverlayElement;
}

class UI_Text : public UI_Element
{
public:
	UI_Text(Ogre::Overlay* overReference, string title, int posX, int posY, int sizeX, int sizeY, string fontTitle, string textContent);
	~UI_Text();

	void setPosition();
	void setSize();

	void setWidth();
	void setHeight();

	void changeFontSize(int fontSize);
	virtual pair<float, float> getPosition() { return position; };
	virtual pair<float, float> getSize() { return size; };

private:
	Ogre::TextAreaOverlayElement* textArea;
	Ogre::OverlayContainer* textPanel;
};

