#include "AppContext.h"

#include <OgreRoot.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>

#include <SDL.h>
///#include <SDL_video.h>
#include <SDL_syswm.h>

AppContext::AppContext(const Ogre::String& appName)
{
	mAppName = appName;
	mFSLayer = new Ogre::FileSystemLayer(appName);
	mRoot = nullptr;
	mOverlaySystem = nullptr;
}

AppContext::~AppContext()
{
	delete mFSLayer;
}

void AppContext::initApp()
{
	createRoot();

	if (oneTimeConfig())
		setup();
}

void AppContext::closeApp()
{
	if (mRoot != nullptr)
	{
		mRoot->saveConfig();
	}
	shutdown();
	delete mRoot;
	mRoot = nullptr;
}

void AppContext::createRoot()
{
	Ogre::String pluginsPath;
	Ogre::String configPath;
	Ogre::String logPath;

	pluginsPath = mFSLayer->getConfigFilePath("plugins.cfg");

	if (!Ogre::FileSystemLayer::fileExists(pluginsPath))
	{	// OGRE_CONFIG_DIR tiene un valor absoluto no portable
		//pluginsPath = Ogre::FileSystemLayer::resolveBundlePath(OGRE_CONFIG_DIR "/plugins" OGRE_BUILD_SUFFIX ".cfg");
		OGRE_EXCEPT(Ogre::Exception::ERR_FILE_NOT_FOUND, "plugins.cfg", "IG2ApplicationContext::createRoot");
	}

	configPath = mFSLayer->getWritablePath("ogre.cfg");
	logPath = mFSLayer->getWritablePath("ogre.log");

	mRoot = new Ogre::Root(pluginsPath, configPath, logPath);

	appPath = pluginsPath; // directorio de la app
	appPath.erase(appPath.find_last_of("\\") + 1, appPath.size() - 1);
	mFSLayer->setHomePath(appPath); // para los archivos de configuración de OGRE
	//////appPath.erase(appPath.find_last_of("\\") + 1, appPath.size() - 1); // quito /bin ¿?¿?

	mOverlaySystem = new Ogre::OverlaySystem();
}

void AppContext::shutdown()
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

void AppContext::setup()
{
	mRoot->initialise(false);
	createWindow(mAppName);
	setWindowGrab(false); // ratón libre

	locateResources();
	loadResources();

	// adds context as listener to process context-level (above the sample level) events
	mRoot->addFrameListener(this);
}

bool AppContext::oneTimeConfig()
{
	if (!mRoot->restoreConfig())
	{
		return mRoot->showConfigDialog(NULL);
	}
	else return true;
}

NativeWindowPair AppContext::createWindow(const Ogre::String& name)
{
	uint32_t w, h;
	Ogre::NameValuePairList miscParams;

	Ogre::ConfigOptionMap ropts = mRoot->getRenderSystem()->getConfigOptions();

	std::istringstream mode(ropts["Video Mode"].currentValue);
	Ogre::String token;
	mode >> w; // width
	mode >> token; // 'x' as seperator between width and height
	mode >> h; // height

	miscParams["FSAA"] = ropts["FSAA"].currentValue;
	miscParams["vsync"] = ropts["VSync"].currentValue;
	miscParams["gamma"] = ropts["sRGB Gamma Conversion"].currentValue;

	if (!SDL_WasInit(SDL_INIT_VIDEO)) SDL_InitSubSystem(SDL_INIT_VIDEO);

	Uint32 flags = SDL_WINDOW_RESIZABLE;

	if (ropts["Full Screen"].currentValue == "Yes") flags = SDL_WINDOW_FULLSCREEN;
	//else flags = SDL_WINDOW_RESIZABLE;

	mWindow.native = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, flags);

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(mWindow.native, &wmInfo);

	miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(size_t(wmInfo.info.win.window));

	mWindow.render = mRoot->createRenderWindow(name, w, h, false, &miscParams);
	return mWindow;
}

void AppContext::setWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(mWindow.native, grab);
	//SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(grab);
}

void AppContext::pollEvents() // from frameStarted
{
	if (mWindow.native == nullptr)
		return;  // SDL events not initialized

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		// SE PULSA LA TECLA 'ESCAPE'
		if (event.key.keysym.sym == SDLK_ESCAPE) {
			//mRoot->queueEndRendering();

			// Esto hace que el bucle de main() se detenga
			// vvv //
			salir = true;
		}

		switch (event.type)
		{
		case SDL_QUIT: // CRUZ DE CERRAR VENTANA
			mRoot->queueEndRendering();
			break;
		case SDL_WINDOWEVENT:
			if (event.window.windowID == SDL_GetWindowID(mWindow.native)) {
				if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					Ogre::RenderWindow* win = mWindow.render;
					//win->resize(event.window.data1, event.window.data2);  // IG2: ERROR 
					win->windowMovedOrResized();
					windowResized(win);
				}
			}
			break;
		default:
			break;
		}
	}
}

void AppContext::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void AppContext::locateResources()
{
	// Recursos en carpeta assets
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		Ogre::FileSystemLayer::resolveBundlePath(appPath + "assets"),
		"FileSystem");

	Ogre::String sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	assert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	Ogre::String arch = genLocs.front().archive->getName();
	Ogre::String type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
	if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsles"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSLES", type, sec);
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL120", type, sec);

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl150"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL150", type, sec);
		}
		else
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL", type, sec);
		}

		if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("glsl400"))
		{
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/GLSL400", type, sec);
		}
	}
	else if (Ogre::GpuProgramManager::getSingleton().isSyntaxSupported("hlsl"))
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch + "/materials/programs/HLSL", type, sec);
	}
}
