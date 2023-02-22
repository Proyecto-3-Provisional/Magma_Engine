
#include <string>
using namespace std;

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

class UIElement
{
public:
	UIElement();
	virtual ~UIElement();

	void show(); 
	void hide(); 
	bool isVisible();

	void setMaterial(string const& materialName);

	virtual void setPosition(float x, float y);
	virtual void setSize(float w, float h);

	virtual void setWidth(float widthValue);
	virtual void setHeight(float heightValue);

	virtual pair<float, float> getPosition();
	virtual pair<float, float> getSize();

	string getElementName();
	
	void setInteractive(bool isInteractive);
	bool getIsFocusNow();

protected:
	
	pair<float, float> position;
	pair<float, float> size;
	bool isInteractive_;
	
};