#include "UI_Element.h"

class UIButton : public UI_Element
{
public:

	UIButton(Ogre::Overlay* overReference, std::string title, std::string imageName, 
		std::string hoverImageName, std::string pressedImageName,
		int posX, int posY, int sizeX, int sizeY);
	virtual ~UIButton();

	void setButtonPosition(float x, float y);
	void setButtonSize(float x, float y);

	void cursorOnButton();
	void mousePressedButton();
	void mouseLeavingButton();

	bool isButtonPressed(); 
	bool isOnButton(); 

	bool isCursorInsideBounds(int x, int y); 

private:

	Ogre::OverlayElement* buttonImage;

	bool pressed;
	bool onButton; 

	int x; 
	int y; 
	int tamX; 
	int tamY; 

	std::string normalButtonName;
	std::string hoverButtonName;
	std::string pressedButtonName;
};