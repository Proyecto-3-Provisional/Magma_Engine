#pragma once

#include <Render/ui_element.h>

namespace magma_engine
{
	class UI_Text : public UI_Element
	{
	public:

		/*
		Creacion de un elemento texto.
		Crea un panel y asigna la posicion y el tamaño del panel, en el cual se
		pueden meter varios elementos pero solo se mete uno. Luego crea un texto
		y asigna sus propios valores, incluyendo el tamaño del texto y el color,
		y lo mete en el panel.
		*/
		UI_Text(std::string overlayName, std::string title,
			float posX, float posY, float sizeX, float sizeY);
		~UI_Text();

		void setFont(std::string font); // Cambia la fuente del texto
		void setText(std::string text); // Cambia el contenido del texto
		void setFontSize(float fontSize); // Cambia el tamaño del texto
		void setTextColor(float r, float g, float b); // Cambia el color del texto

	};

}

