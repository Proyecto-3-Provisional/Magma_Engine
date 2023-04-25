#include <Render/ui_element.h>

namespace magma_engine
{
	class UIButton : public UI_Element
	{
	public:

		// Creacion del elemento boton 
		UIButton(std::string overReference, std::string imageName,
			std::string hoverImageName, std::string pressedImageName,
			float posX, float posY, float sizeX, float sizeY);
		virtual ~UIButton();
	};
}

