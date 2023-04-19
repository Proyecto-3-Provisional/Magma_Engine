#include <EC/component.h>

#include <string>

class UIButton;

class Button : public ec::Component
{
public:
	Button();
	Button(std::string overlayName, std::string imageName, std::string hoverImageName, std::string pressedImageName,
		float width, float height, float x, float y);

	virtual ~Button();

	virtual bool initComponent();

	virtual void render() {};

	virtual void onEnable();
	virtual void onDisable();

	std::string GetName();

	virtual void start();
	virtual void update(float deltaTime);

	void setInteractive(bool interactive);

	bool isCursorInsideBounds(int x, int y);
	bool isButtonPressed();

private:

	//InputManager* input;
	UIButton* button;

	std::string buttonName;
	std::string normalButtonName;
	std::string hoverButtonName;
	std::string pressedButtonName;

	bool pressed;

	float tamX;
	float tamY;
	float posX;
	float posY;
	float screenHeight;
	float screenWidth;

	bool interactive;
};