#include <string>
using namespace std;

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

class UI_Element
{
public:
	UI_Element(Ogre::Overlay* overReference, string name);
	~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	//virtual void setPosition(float x, float y) {};
	//virtual void setSize(float w, float h) {};

	//virtual void setWidth(float widthValue) {};
	//virtual void setHeight(float heightValue) {};

	pair<float, float> getPosition();
	pair<float, float> getSize();

	string getElementName();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	pair<float, float> position;
	pair<float, float> size;
	
	Ogre::OverlayManager* overlayMan_;
	Ogre::Overlay* overlay_;

	string name;
	bool isInteractive_;
};