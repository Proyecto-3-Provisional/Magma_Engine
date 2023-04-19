#include <EC/text.h>

#include <Render/UI_Text.h>
#include <Render/UI_Manager.h>

Text::Text(std::string overlayName, std::string title, std::string font, std::string textCont,
	float x, float y, float width, float height, float r, float g, float b) : Component()
{
	textReference = overlayName;

	textTitle = title; 
	fontName = font;
	textContent = textCont; 

	tamX = width;
	tamY = height;

	posX = x;
	posY = y;

	red = r; 
	green = g; 
	blue = b; 

	screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
}

Text::~Text() {}

std::string Text::GetName()
{
	return textTitle;
}

bool Text::initComponent() { return true; }

void Text::start()
{
	text = Singleton<UI_Manager>::instance()->createElement<UI_Text>(textReference, textTitle, posX, posY, tamX, tamY);

	text->setTextPosition(posX, posY);
	text->setTextSize(tamX, tamY);

	text->setFont(fontName); 
	text->setText(textContent); 
	text->setTextColor(red, green, blue); 
}

void Text::onEnable()
{
	if (text != nullptr)
		text->showElement();
}

void Text::onDisable()
{
	text->hideElement();
}

void Text::update(float deltaTime) 
{
	float newWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
	float newHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();

	if (newWidth != 0 && newHeight != 0 && screenWidth != 0 && screenHeight != 0)
	{
		text->setTextPosition(posX * (newWidth / screenWidth), posY * (newHeight / screenHeight));
		text->setTextSize(tamX * (newWidth / screenWidth), tamY * (newHeight / screenHeight));
		changeSizeText(tamY * (newHeight / screenHeight)); 
	}
}

void Text::changeFontText(std::string newFont)
{
	text->setFont(newFont);
}

void Text::changeText(std::string newText)
{
	text->setText(newText);
}

void Text::changeSizeText(float size)
{
	text->setFontSize(size); 
}

void Text::changeColorText(float r, float g, float b)
{
	text->setTextColor(r, g, b); 
}