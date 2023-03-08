#include "UI_Element.h"

class UI_Image : public UI_Element
{
public:
	UI_Image(Ogre::Overlay* overReference ,std::string title, std::string imageName,
		Ogre::Real posX, Ogre::Real posY, Ogre::Real sizeX, Ogre::Real sizeY);
	virtual ~UI_Image();

	void setImagePosition(double x, double y);
	void setImageSize(double x, double y);
	void changeImage(std::string title, std::string imageName);

private:
	Ogre::OverlayElement* imageUI = nullptr;
};
