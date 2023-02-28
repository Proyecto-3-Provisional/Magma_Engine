#include "render_manager_context.h"

#include <OgreRoot.h>
#include <OgreFileSystemLayer.h>
#include <OgreGpuProgramManager.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreLogManager.h>

#include <SDL.h>
///#include <SDL_video.h>
#include <SDL_syswm.h>

RenderManagerContext::RenderManagerContext(const Ogre::String& appName)
	: exitRequest(false)
{
	mAppName = appName;
	mFSLayer = new Ogre::FileSystemLayer(appName);
	mRoot = nullptr;
	mOverlaySystem = nullptr;
}

RenderManagerContext::~RenderManagerContext()
{
	delete mFSLayer;
}

bool RenderManagerContext::initApp()
{
	try {
		createRoot();

		if (oneTimeConfig())
			setup();
	}
	catch (Ogre::Exception& e) {
		Ogre::String errMsg = "An exception has occured: " + e.getFullDescription() + "\n";
		Ogre::LogManager::getSingleton().logMessage(errMsg);
		return false;
	}
	return true;
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

void RenderManagerContext::createRoot()
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
	setWindowGrab(false); // ratón libre

	locateResources();
	loadResources();

	// adds context as listener to process context-level (above the sample level) events
	mRoot->addFrameListener(this);
}

bool RenderManagerContext::oneTimeConfig()
{
	if (!mRoot->restoreConfig())
	{
		return mRoot->showConfigDialog(NULL);
	}
	else return true;
}

NativeWindowPair RenderManagerContext::createWindow(const Ogre::String& name)
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

void RenderManagerContext::setWindowGrab(bool _grab)
{
	SDL_bool grab = SDL_bool(_grab);
	SDL_SetWindowGrab(mWindow.native, grab);
	//SDL_SetRelativeMouseMode(grab);
	SDL_ShowCursor(grab);
}

bool RenderManagerContext::renderFrame()
{
	return mRoot->renderOneFrame();
}

void RenderManagerContext::loadResources()
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void RenderManagerContext::locateResources()
{
	// Recursos en carpeta assets
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
		Ogre::FileSystemLayer::resolveBundlePath(appPath + "assets"),
		"FileSystem");

	Ogre::String sec = Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME;
	const Ogre::ResourceGroupManager::LocationList genLocs =
		Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(sec);

	assert(!genLocs.empty(), ("Resource Group '" + sec + "' must contain at least one entry").c_str());

	Ogre::String arch = genLocs.front().archive->getName();
	Ogre::String type = genLocs.front().archive->getType();

	// Add locations for supported shader languages
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
