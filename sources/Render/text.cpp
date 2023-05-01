#include <Render/text.h>

#include <Render/UI_Text.h>
#include <Render/UI_Manager.h>

namespace magma_engine
{
	Text::Text() : Component(), textReference(), textTitle(), fontName(), textContent(), posX(), posY(), tamX(), tamY(), red(), green(), blue()
	{

	}

	Text::~Text() {}

	std::string Text::GetName()
	{
		return textTitle;
	}

	bool Text::initComponent(std::map<std::string, std::string> args)
	{
		textReference = args["overlayName"];

		textTitle = args["title"];
		fontName = args["font"];
		textContent = args["textCont"];

		tamX = stof(args["width"]);
		tamY = stof(args["height"]);

		posX = stof(args["x"]);
		posY = stof(args["y"]);

		red = stof(args["r"]);
		green = stof(args["g"]);
		blue = stof(args["b"]);

		screenWidth = (float)Singleton<RenderManager>::instance()->getWinWidth();
		screenHeight = (float)Singleton<RenderManager>::instance()->getWinHeight();
		return true;
	}

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
}

