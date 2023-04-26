#pragma once

#include <Render/ui_element.h>

namespace magma_engine
{
	class UI_Progress_Bar : public UI_Element
	{
	public:

		/*
		Creacion de un elemento barra de progreso.
		Crea un panel y asigna la posicion y el tamaño del panel, en el cual se
		pueden meter varios elementos pero solo se mete uno.
		*/
		UI_Progress_Bar(std::string overReference, std::string imageName, 
			float posX, float posY, float sizeX, float sizeY);
		~UI_Progress_Bar();
	};

}