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
	public:
		explicit RenderManagerContext(const Ogre::String& appName = OGRE_VERSION_NAME);
		explicit RenderManagerContext(const Ogre::String& appName,
			uint32_t w, uint32_t h, bool fScr, bool vSyn, int fsaa, bool gamm);
		~RenderManagerContext();

		// Obtener la RenderWindow; posee el contexto en OpenGL
		Ogre::RenderWindow* getRenderWindow() const;
		// Obtener raíz de Ogre
		Ogre::Root* getRoot() const;
		// Obtener sistema de Overlay
		Ogre::OverlaySystem* getOverlaySystem() const;

		// Inicializar sistema de renderizado y recursos
		Ogre::SceneManager* initApp();

		// Cerrar la aplicación, tras salvar la configuración
		void closeApp();

		// Interfaz de callbacks copiada de varios listeners para usarse aquí
		bool frameStarted(const Ogre::FrameEvent& evt);
		bool frameEnded(const Ogre::FrameEvent& evt);
		void windowMoved(Ogre::RenderWindow* rw);
		void windowResized(Ogre::RenderWindow* rw);
		bool windowClosing(Ogre::RenderWindow* rw);
		void windowClosed(Ogre::RenderWindow* rw);
		void windowFocusChange(Ogre::RenderWindow* rw);

		// Crear la raíz de Ogre
		void createRoot();

		// Configura las opciones de inicio para Ogre
		bool oneTimeConfig();

		// Preparar el contexto tras la configuración
		void setup();

		// Crear una nueva ventana para renderizar
		NativeWindowPair createWindow(const Ogre::String& name);

		// Confinar ratón dentro de la ventana
		void setWindowGrab(bool grab);

		// Encontrar grupos de recursos para el contexto
		void locateResources();

		// Cargar grupos de recursos para el contexto
		void loadResources();

		// Limpiar y cerrar el contexto
		void shutdown();

		// Reaccionar al reescalado de ventana
		void notifyWindowResized();

		// Renderizar un fotograma
		bool renderFrame();

		int getWinWidth();
		int getWinHeight();

		void setCursor(bool grab);
		Ogre::Root* getRoot();
		Ogre::OverlaySystem* getOverlaySystem();

	protected:
		bool cursorGrab;
		// Nombre de la aplicación
		Ogre::String mAppName;		
		// Ruta a la aplicación
		Ogre::String appPath;				
		// Ventana
		NativeWindowPair mWindow;			
		// Raíz de Ogre
		Ogre::Root* mRoot;					
		// Abstracción del sist. de ficheros
		Ogre::FileSystemLayer* mFSLayer;	
		// Requerido por OverlayManager (UI)
		Ogre::OverlaySystem* mOverlaySystem;

		// Config. de ventana
		uint32_t winWidth;
		uint32_t winHeight;
		bool fullScreenEnabled;
		bool vSyncEnabled;
		int fsaaLevel;
		bool gammaEnabled;
	};
}


