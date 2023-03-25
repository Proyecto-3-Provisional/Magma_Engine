#include "UI_Element.h"

class UI_Image : public UI_Element
{
public:
	UI_Image(Ogre::Overlay* overReference ,std::string title, std::string imageName,
		float posX, float posY, float sizeX, float sizeY);
	~UI_Image();

	void setImagePosition(float x, float y);
	void setImageSize(float x, float y);
	void changeImage(std::string title, std::string imageName);

	void updateImage();

private:
	Ogre::OverlayElement* imageUI = nullptr;
	float screenwidth = 1;
	float screenheight = 1;
	float originalwidth;
	float originalheight;
	float originalposx;
	float originalposy;

};
