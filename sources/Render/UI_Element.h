#include <Overlay/OgreOverlay.h>
#include <Overlay/OgreOverlayManager.h>
#include <Overlay/OgreOverlayContainer.h>

#include <string>
using namespace std;


class UI_Element
{
public:
	UI_Element(Ogre::Overlay* overReference, string name, int posX, int posY, int sizeX, int sizeY);
	~UI_Element();

	void showElement(); 
	void hideElement(); 
	bool isElementVisible();

	void setPanelPosition(float x, float y) {};
	void setPanelSize(float w, float h) {};

	pair<float, float> getPosition();
	pair<float, float> getSize();

	string getElementName();
	
	void setInteractive(bool isInteractive) {};

protected:
	
	pair<float, float> position;
	pair<float, float> size;
	
	Ogre::OverlayManager* overlayMan_;
	Ogre::Overlay* overlay_;
	Ogre::OverlayContainer* panel;


	string name;
	bool isInteractive_;
};