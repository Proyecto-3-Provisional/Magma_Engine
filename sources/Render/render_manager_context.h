#pragma once

#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <Overlay/OgreOverlaySystem.h>

// Para SDL_Window (y evitar a SDL.h aquí (roba el main()))
#include <SDL_video.h>

namespace magma_engine
{
	// Alias para SDL_Window
	typedef SDL_Window NativeWindowType;

	// Enlace entre una RenderWindow y una Window de una plataforma específica
	struct NativeWindowPair
	{
		Ogre::RenderWindow* render = nullptr;
		NativeWindowType* native = nullptr;
	};

	// Clase base responsable de establecer un contexto común para aplicaciones
	// con ventana. La subclase debe especificar los callbacks a eventos.
	class RenderManagerContext : public Ogre::FrameListener
	{
	protected:
		explicit RenderManagerContext(const Ogre::String& appName = OGRE_VERSION_NAME);
		explicit RenderManagerContext(const Ogre::String& appName,
			uint32_t w, uint32_t h, bool fScr, bool vSyn, int fsaa, bool gamm);
	public:
		virtual ~RenderManagerContext();

		// Obtener la RenderWindow; posee el contexto en OpenGL
		Ogre::RenderWindow* getRenderWindow() const;
		// Obtener raíz de Ogre
		Ogre::Root* getRoot() const;
		// Obtener sistema de Overlay
		Ogre::OverlaySystem* getOverlaySystem() const;

		// Inicializar sistema de renderizado y recursos
		bool initApp();

		// Cerrar la aplicación, tras salvar la configuración
		void closeApp();

		// Interfaz de callbacks copiada de varios listeners para usarse aquí
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual void windowMoved(Ogre::RenderWindow* rw);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual bool windowClosing(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);

		// Crear la raíz de Ogre
		virtual void createRoot();

		// Configura las opciones de inicio para Ogre
		virtual bool oneTimeConfig();

		// Preparar el contexto tras la configuración
		virtual void setup();

		// Crear una nueva ventana para renderizar
		virtual NativeWindowPair createWindow(const Ogre::String& name);

		// Confinar ratón dentro de la ventana
		void setWindowGrab(bool grab);

		// Encontrar grupos de recursos para el contexto
		virtual void locateResources();

		// Cargar grupos de recursos para el contexto
		virtual void loadResources();

		// Limpiar y cerrar el contexto
		virtual void shutdown();

		// Reaccionar al reescalado de ventana
		void notifyWindowResized();

		// Renderizar un fotograma
		bool renderFrame();

		int getWinWidth();
		int getWinHeight();

	protected:
		bool cursorGrab;

		Ogre::String mAppName;				// Nombre de la aplicación
		Ogre::String appPath;				// Ruta a la aplicación

		NativeWindowPair mWindow;			// Ventana
		Ogre::Root* mRoot;					// Raíz de Ogre
		Ogre::FileSystemLayer* mFSLayer;	// Abstracción del sist. de ficheros
		Ogre::OverlaySystem* mOverlaySystem;// Requerido por OverlayManager (UI)

		// Config. de ventana
		uint32_t winWidth;
		uint32_t winHeight;
		bool fullScreenEnabled;
		bool vSyncEnabled;
		int fsaaLevel;
		bool gammaEnabled;
	};
}


