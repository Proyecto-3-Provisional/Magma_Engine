#include <Render/ui_element.h>

class UI_Image : public UI_Element
{
public:
	//Metodo de creacion de un elemento imagen 
	UI_Image(std::string overReference, std::string imageName,
		float posX, float posY, float sizeX, float sizeY);
	~UI_Image();
};
