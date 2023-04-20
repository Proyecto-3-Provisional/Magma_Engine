#pragma once

#include <Render/ui_element.h>

class UI_Text : public UI_Element
{
public:

	//Metodo de creacion de un elemento texto
	UI_Text(std::string overlayName, std::string title,
		float posX, float posY, float sizeX, float sizeY);
	~UI_Text();

	//Metodo para establecer un nuevo contenido, fuente,
	//tamaño o color de texto 
	void setFont(std::string font); 
	void setText(std::string text);
	void setFontSize(float fontSize);
	void setTextColor(float r, float g, float b);
};
