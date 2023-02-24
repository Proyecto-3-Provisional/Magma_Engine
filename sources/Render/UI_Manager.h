#include <memory>
#include <string>
#include <vector>

using namespace std;

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

class UI_Element;

class UI_Manager
{
public:
	UI_Manager();
	~UI_Manager();

	void init();

	void update();

	void cleanPanel();
	
	void createText(string textPanelName, int posX, int posY, int sizeX, int sizeY, string fontName, string textContent);

private:

	Ogre::OverlayManager* overlayMngr_;
	Ogre::Overlay* overlay;
	vector<UI_Element*> elements;

};