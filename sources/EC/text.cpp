#include "text.h"

Text::Text(std::string overlayName, std::string font, std::string textCont,
	float x, float y, float width, float height) : Component()
{
	textName = overlayName;
	fontName = font;
	textContent = textCont; 

	tamX = width;
	tamY = height;

	posX = x;
	posY = y;

	start(); 
}

Text::~Text() {}

std::string Text::GetName()
{
	return textName;
}

void Text::start()
{
	/*text->setPanelSize(tamX, tamY);
	text->setPanelPosition(posX, posY);
	text->setText(textContent); */
}

void Text::update() {}

void Text::changeText(std::string newText)
{
	//text->setText(newText);
}