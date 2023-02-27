#include "UI_Element.h"

class UI_Image : public UI_Element
{
public:
	UI_Image(Ogre::Overlay* overReference ,std::string title, std::string imageName,
		int posX, int posY, int sizeX, int sizeY);
	virtual ~UI_Image();

	void setImagePosition(float x, float y);
	void setImageSize(float x, float y);
	void changeImage(std::string imageName);

private:
	Ogre::OverlayElement* imageUI;
};
