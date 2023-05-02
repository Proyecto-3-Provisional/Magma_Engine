#include <Render/render_manager_context.h>

#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreLogManager.h>
#include <OgreMeshManager.h>

#include <SDL.h>
#include <SDL_syswm.h>

namespace magma_engine
{
	RenderManagerContext::RenderManagerContext(const Ogre::String& appName)
		: winWidth(1280), winHeight(720), fullScreenEnabled(false), vSyncEnabled(true),
		fsaaLevel(0), gammaEnabled(false)
	{
		mAppName = appName;
		mFSLayer = new Ogre::FileSystemLayer(appName);
		mRoot = nullptr;
		mOverlaySystem = nullptr;
		cursorGrab = false;
	}

	RenderManagerContext::RenderManagerContext(const Ogre::String& appName,
		uint32_t w, uint32_t h, bool fScr, bool vSyn, int fsaa, bool gamm)
	{
		mAppName = appName;
		mFSLayer = new Ogre::FileSystemLayer(appName);
		mRoot = nullptr;
		mOverlaySystem = nullptr;
		cursorGrab = false;
		winWidth = w;
		winHeight = h;
		fullScreenEnabled = fScr;
		vSyncEnabled = vSyn;
		fsaaLevel = fsaa;
		gammaEnabled = gamm;
	}

	RenderManagerContext::~RenderManagerContext()
	{
		delete mFSLayer;
	}

	Ogre::RenderWindow* RenderManagerContext::getRenderWindow() const
	{
		return mWindow.render;
	}

	Ogre::Root* RenderManagerContext::getRoot() const
	{
		return mRoot;
	}

	Ogre::OverlaySystem* RenderManagerContext::getOverlaySystem() const
	{
		return mOverlaySystem;
	}

	Ogre::SceneManager* RenderManagerContext::initApp()
	{
		Ogre::SceneManager* mSM = nullptr;
		try {
			createRoot();

			if (oneTimeConfig()) {
				setup();

				mSM = mRoot->createSceneManager();
				mSM->addRenderQueueListener(mOverlaySystem);

				Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800",
					Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
					Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), // vector normal, vector up
					1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::UNIT_X);
			}
		}
		catch (Ogre::Exception& e) {
			Ogre::String errMsg = "An exception has occured: " +
				e.getFullDescription() + "\n";
			Ogre::LogManager::getSingleton().logMessage(errMsg);
		}
		return mSM;
	}

	void RenderManagerContext::closeApp()
	{
		if (mRoot != nullptr)
		{
			mRoot->saveConfig();
		}
		shutdown();
		delete mRoot;
		mRoot = nullptr;
	}

	bool RenderManagerContext::frameStarted(const Ogre::FrameEvent& evt)
	{
		return true;
	}

	bool RenderManagerContext::frameEnded(const Ogre::FrameEvent& evt)
	{
		return true;
	}

	void RenderManagerContext::windowMoved(Ogre::RenderWindow* rw)
	{
	}

	void RenderManagerContext::windowResized(Ogre::RenderWindow* rw)
	{
		winWidth = rw->getWidth();
		winHeight = rw->getHeight();
	}

	bool RenderManagerContext::windowClosing(Ogre::RenderWindow* rw)
	{
		return true;
	}

	void RenderManagerContext::windowClosed(Ogre::RenderWindow* rw)
	{
	}

	void RenderManagerContext::windowFocusChange(Ogre::RenderWindow* rw)
	{
	}

	void RenderManagerContext::createRoot()
	{
		Ogre::String pluginsPath;
		Ogre::String configPath;
		Ogre::String logPath;

		pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");

		if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
			OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg",
				"RenderManagerContext::createRoot");

		configPath = mFSLayer->getWritablePath("ogre.cfg");
		logPath = mFSLayer->getWritablePath("ogre.log");

		mRoot = new Ogre::Root(pluginsPath, configPath, logPath);

		appPath = pluginsPath;
		appPath.erase(appPath.find_last_of("\\") + 1, appPath.size() - 1);
		mFSLayer->setHomePath(appPath);

		mOverlaySystem = new Ogre::OverlaySystem();
	}

	void RenderManagerContext::shutdown()
	{
		if (mWindow.render != nullptr)
		{
			mRoot->destroyRenderTarget(mWindow.render);
			mWindow.render = nullptr;
		}

		delete mOverlaySystem;
		mOverlaySystem = nullptr;

		if (mWindow.native != nullptr)
		{
			SDL_DestroyWindow(mWindow.native);
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			mWindow.native = nullptr;
		}
	}

	void RenderManagerContext::setup()
	{
		mRoot->initialise(false);
		createWindow(mAppName);
		setWindowGrab(cursorGrab);

		locateResources();
		loadResources();

		// adds context as listener to process context-level (above the sample level) events
		mRoot->addFrameListener(this);
	}

	// Esto solo pasa cuando se inicia el contexto y no al restablecerlo
	bool RenderManagerContext::oneTimeConfig()
	{
		if (!mRoot->restoreConfig())
		{
			return mRoot->showConfigDialog(NULL);
		}
		else return true;
	}

	// La ventana ha de ser de SDL para poder registrar eventos
	// Por defecto se lee el alto y el ancho de ogre.cfg
	NativeWindowPair RenderManagerContext::createWindow(const Ogre::String& name)
	{
		uint32_t w, h;
		Ogre::NameValuePairList miscParams;

		Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();


		std::istringstream mode(ropts["Video Mode"].currentValue);
		Ogre::String token;
		mode >> w;		// width
		mode >> token;	// 'x' as seperator between width and height
		mode >> h;		// height

		miscParams["vsync"] = ropts["VSync"].currentValue; // Yes / No
		miscParams["FSAA"] = ropts["FSAA"].currentValue; // 0 / 2 / 4 / 8 / 16
		miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue; // Yes / No

		if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

		Uint32 flags;
		// Yes / NO
		if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN;
		else flags = SDL_WINDOW_RESIZABLE;

		// modificaciones a la configuración por defecto
		w = winWidth;
		h = winHeight;
		if (fullScreenEnabled) flags = SDL_WINDOW_FULLSCREEN;
		else flags = SDL_WINDOW_RESIZABLE;
		if (vSyncEnabled) miscParams["vsync"] = "Yes";
		else miscParams["vsync"] = "No";
		if (gammaEnabled) miscParams["gamma"] = "Yes";
		else miscParams["gamma"] = "No";
		if (fsaaLevel != 0 && fsaaLevel != 2 && fsaaLevel != 4
			&& fsaaLevel != 8 && fsaaLevel != 16) fsaaLevel = 0;
		miscParams["FSAA"] = Ogre::StringConverter::toString(fsaaLevel);
		// modificaciones

		mWindow.native = SDL_CreateWindow(name.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

		SDL_SysWMinfo wmInfo;
		SDL_VERSION(&wmInfo.version);
		SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

		miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(
			size_t(wmInfo.info.win.window));

		mWindow.render = mRoot->createRenderWindow(name, w, h, false, &miscParams);
		return mWindow;
	}

	/*
	TRUE
		- el ratón es visible en la ventana
		- el ratón no va más allá de los límites si la ventana está en foco
	FALSE
		- el ratón no es visible si se pasa por la ventana
		- el ratón sobrevuela la ventana, y se puede seleccionar otras con el cursor
	*/
	void RenderManagerContext::setWindowGrab(bool _grab)
	{
		SDL_bool grab = SDL_bool(_grab);
		SDL_SetWindowGrab(mWindow.native, grab);
		//SDL_SetRelativeMouseMode(grab);
		SDL_ShowCursor(grab);
	}

	void RenderManagerContext::notifyWindowResized()
	{
		Ogre::RenderWindow* win = mWindow.render;
		win->windowMovedOrResized();
		windowResized(win);
	}

	bool RenderManagerContext::renderFrame()
	{
		return mRoot->renderOneFrame();
	}

	// Simplemente se inicializan todos los grupos
	void RenderManagerContext::loadResources()
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

	// Los resursos gráficos se buscan en el directorio '/executables/assets/graphics'
	// Se añaden ubicaciones para lenguajes de sharders con soporte
	void RenderManagerContext::locateResources()
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
			Ogre::FileSystemLayer::resolveBundlePath(appPath + "assets/graphics"),
			"FileSystem");

		Ogre::String sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
		const Ogre::ResourceGroupManager::LocationList genLocs =
			Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

		// "Resource Group 'sec' must contain at least one entry"
		assert(!genLocs.empty());

		Ogre::String arch = genLocs.front().archive->getName();
		Ogre::String type = genLocs.front().archive->getType();

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
				"/materials/programs/GLSLES", type, sec);
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
				"/materials/programs/GLSL120", type, sec);

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
					"/materials/programs/GLSL150", type, sec);
			}
			else
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
					"/materials/programs/GLSL", type, sec);
			}

			if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
			{
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
					"/materials/programs/GLSL400", type, sec);
			}
		}
		else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch +
				"/materials/programs/HLSL", type, sec);
		}
	}

	int RenderManagerContext::getWinWidth() {
		return winWidth;
	}

	int RenderManagerContext::getWinHeight() {
		return winHeight;
	}
	void RenderManagerContext::setCursor(bool grab)
	{
		cursorGrab = grab;
	}
	Ogre::Root* RenderManagerContext::getRoot()
	{
		return mRoot;
	}
	Ogre::OverlaySystem* RenderManagerContext::getOverlaySystem()
	{
		return mOverlaySystem;
	}
}


