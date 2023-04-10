#include "component.h"

#include <string>


class Button : public ec::Component
{
public:

	Button(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName,
		float width, float height, float x, float y);

	virtual ~Button();

	std::string GetName();

	virtual void start();
	virtual void update();

private:

	//InputManager* input;
	//UIButton* button;

	std::string buttonName;
	std::string normalButtonName;
	std::string hoverButtonName;
	std::string pressedButtonName;

	bool pressed;

	float tamX;
	float tamY;
	float posX;
	float posY;
};