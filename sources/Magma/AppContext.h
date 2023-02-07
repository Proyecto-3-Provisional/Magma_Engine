#pragma once

#include <string>

#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <Overlay/OgreOverlaySystem.h>

#include <SDL_video.h> // para SDL_Window (y evitar a SDL.h aquí (roba el main()))

typedef SDL_Window NativeWindowType;

//link between a renderwindow and a platform specific window
struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};

//Base class responsible for setting up a common context for applications.
//Subclass to implement specific event callbacks.
class AppContext : public Ogre::FrameListener
{
public:
	explicit AppContext(const Ogre::String& appName = OGRE_VERSION_NAME);

	virtual ~AppContext();

	//get the main RenderWindow owns the context on OpenGL
	Ogre::RenderWindow* getRenderWindow() const { return mWindow.render; }

	Ogre::Root* getRoot() const { return mRoot; }

	Ogre::OverlaySystem * getOverlaySystem() const { return mOverlaySystem; }

	//This function initializes the render system and resources.
	void initApp();

	//This function closes down the application - saves the configuration then shutdowns.
	void closeApp();

	// callback interface copied from various listeners to be used by ApplicationContext
	virtual bool frameStarted(const Ogre::FrameEvent& evt) { pollEvents(); return true; }
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
	virtual void windowMoved(Ogre::RenderWindow* rw) {}
	virtual void windowResized(Ogre::RenderWindow* rw) {}
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	virtual void windowClosed(Ogre::RenderWindow* rw) {}
	virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

	//Sets up the context after configuration.
	virtual void setup();

	//Creates the OGRE root.
	virtual void createRoot();

	//Configures the startup settings for OGRE. I use the config dialog here,
	//but you can also restore from a config file. Note that this only happens
	//when you start the context, and not when you reset it.
	virtual bool oneTimeConfig();

	//When input is grabbed the mouse is confined to the window.
	void setWindowGrab(bool grab);

	//Finds context-wide resource groups. I load paths from a config file here,
	//but you can choose your resource locations however you want.
	virtual void locateResources();

	//Loads context-wide resource groups. I chose here to simply initialise all
	//groups, but you can fully load specific ones if you wish.
	virtual void loadResources();

	//Cleans up and shuts down the context.
	virtual void shutdown();

	//process all window events since last call
	void pollEvents();

	//Create a new render window
	//You must use SDL and not an auto-created window as SDL does not get the events otherwise.
	//By default the values from ogre.cfg are used for w, h and miscParams.
	virtual NativeWindowPair createWindow(const Ogre::String& name);

	bool salir = false; // TEMPORALMENTE --- ¿Salir de la app?

protected:

	Ogre::Root* mRoot;        // OGRE root
	NativeWindowPair mWindow; // the window
	
	Ogre::String appPath;

	Ogre::OverlaySystem* mOverlaySystem;
	Ogre::FileSystemLayer* mFSLayer;

	Ogre::String mAppName;
};
