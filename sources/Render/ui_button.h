#include <Render/ui_element.h>

class UIButton : public UI_Element
{
public:

	//Metodo de creacion del elemento boton 
	UIButton(std::string overReference, std::string imageName,
		std::string hoverImageName, std::string pressedImageName,
		float posX, float posY, float sizeX, float sizeY);
	virtual ~UIButton();
};