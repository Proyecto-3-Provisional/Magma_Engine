#include <memory>
#include <vector>

using namespace std;

namespace Ogre {
	class Overlay;
	class OverlayContainer;
	class OverlayManager;
}

class UI_Manager
{
public:
	UI_Manager(int dimensionX, int dimensionY);
	~UI_Manager();

	//static UI_Manager* GetInstance();

	void init();

	void update();

	void cleanPanel();

	// void addUIElement();

private:
	static unique_ptr<UI_Manager> instance;

	Ogre::OverlayManager& overlayMngr_ = Ogre::OverlayManager::getSingleton();;
	Ogre::Overlay* overlay;
	Ogre::OverlayContainer* generalPanel;

};