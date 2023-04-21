#pragma once

#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <Overlay/OgreOverlaySystem.h>

// Para SDL_Window (y evitar a SDL.h aqu� (roba el main()))
#include <SDL_video.h>

namespace magma_engine
{
	// Alias para SDL_Window
	typedef SDL_Window NativeWindowType;

	// Enlace entre una RenderWindow y una Window de una plataforma espec�fica
	struct NativeWindowPair
	{
		Ogre::RenderWindow* render = nullptr;
		NativeWindowType* native = nullptr;
	};

	// Clase base responsable de establecer un contexto com�n para aplicaciones
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
		// Obtener ra�z de Ogre
		Ogre::Root* getRoot() const;
		// Obtener sistema de Overlay
		Ogre::OverlaySystem* getOverlaySystem() const;

		// Inicializar sistema de renderizado y recursos
		bool initApp();

		// Cerrar la aplicaci�n, tras salvar la configuraci�n
		void closeApp();

		// Interfaz de callbacks copiada de varios listeners para usarse aqu�
		virtual bool frameStarted(const Ogre::FrameEvent& evt);
		virtual bool frameEnded(const Ogre::FrameEvent& evt);
		virtual void windowMoved(Ogre::RenderWindow* rw);
		virtual void windowResized(Ogre::RenderWindow* rw);
		virtual bool windowClosing(Ogre::RenderWindow* rw);
		virtual void windowClosed(Ogre::RenderWindow* rw);
		virtual void windowFocusChange(Ogre::RenderWindow* rw);

		// Crear la ra�z de Ogre
		virtual void createRoot();

		// Configura las opciones de inicio para Ogre
		virtual bool oneTimeConfig();

		// Preparar el contexto tras la configuraci�n
		virtual void setup();

		// Crear una nueva ventana para renderizar
		virtual NativeWindowPair createWindow(const Ogre::String& name);

		// Confinar rat�n dentro de la ventana
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

		Ogre::String mAppName;				// Nombre de la aplicaci�n
		Ogre::String appPath;				// Ruta a la aplicaci�n

		NativeWindowPair mWindow;			// Ventana
		Ogre::Root* mRoot;					// Ra�z de Ogre
		Ogre::FileSystemLayer* mFSLayer;	// Abstracci�n del sist. de ficheros
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


