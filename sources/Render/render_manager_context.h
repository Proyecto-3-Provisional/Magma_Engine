#pragma once

#include <string>

#include <OgreFileSystemLayer.h>
#include <OgreFrameListener.h>
#include <Overlay/OgreOverlaySystem.h>

#include <SDL_video.h> // para SDL_Window (y evitar a SDL.h aqu� (roba el main()))

// Alias para SDL_Window
typedef SDL_Window NativeWindowType;

// Enlace entre una RenderWindow y una Window de una plataforma espec�fica
struct NativeWindowPair
{
	Ogre::RenderWindow* render = nullptr;
	NativeWindowType* native = nullptr;
};

// Clase base responsable de establecer un contexto com�n para aplicaciones
// La subclase debe especificar los callbacks a eventos
class RenderManagerContext : public Ogre::FrameListener
{
public:
	explicit RenderManagerContext(const Ogre::String& appName = OGRE_VERSION_NAME);
	virtual ~RenderManagerContext();

	// Obtener la RenderWindow; posee el contexto en OpenGL
	Ogre::RenderWindow* getRenderWindow() const { return mWindow.render; }
	// Obtener ra�z de Ogre
	Ogre::Root* getRoot() const { return mRoot; }
	// Obtener sistema de Overlay
	Ogre::OverlaySystem* getOverlaySystem() const { return mOverlaySystem; }

	// Inicializar sistema de renderizado y recursos
	bool initApp();

	// Cerrar la aplicaci�n, tras salvar la config.
	void closeApp();

	// Interfaz de callbacks copiada de varios listeners para usarse aqu�
	virtual bool frameStarted(const Ogre::FrameEvent& evt) { pollEvents(); return true; }
	virtual bool frameEnded(const Ogre::FrameEvent& evt) { return true; }
	virtual void windowMoved(Ogre::RenderWindow* rw) {}
	virtual void windowResized(Ogre::RenderWindow* rw) {}
	virtual bool windowClosing(Ogre::RenderWindow* rw) { return true; }
	virtual void windowClosed(Ogre::RenderWindow* rw) {}
	virtual void windowFocusChange(Ogre::RenderWindow* rw) {}

	// Crear la ra�z de Ogre
	virtual void createRoot();

	// Configura las opciones de inicio para Ogre
	// Se usa el di�logo de config., pero tambi�n se puede restaurar de un fichero
	// Esto solo pasa cuando se inicia el contexto y no al restablecerlo
	virtual bool oneTimeConfig();

	// Preparar el contexto tras la configuraci�n
	virtual void setup();

	//Create a new render window
	//You must use SDL and not an auto-created window as SDL does not get the events otherwise.
	//By default the values from ogre.cfg are used for w, h and miscParams.
	virtual NativeWindowPair createWindow(const Ogre::String& name);

	// Cuando se toma la entrada, �el rat�n queda confinado en la ventana?
	void setWindowGrab(bool grab);

	// Encontrar grupos de recursos para el contexto
	// En este caso se buscan en el dir. '/executables/assets';
	//		no se lee de fichero qu� cargar
	virtual void locateResources();

	// Cargar grupos de recursos para el contexto
	// Aqu� simplemente se inicializan todos los grupos,
	//		pero se podr�an cargar completamente algunos espec�cifos
	virtual void loadResources();

	// Limpiar y cerrar el contexto
	virtual void shutdown();

	// Procesar todos los eventos de ventana desde la �ltima llamada
	virtual void pollEvents() = 0;
	// Renderizar un fotograma
	bool renderFrame();
	// �Se debe salir del bucle ppal.?
	bool exitRequested();

protected:
	Ogre::String mAppName;				// Nombre de la aplicaci�n
	Ogre::String appPath;				// Ruta a la aplicaci�n

	NativeWindowPair mWindow;			// Ventana
	Ogre::Root* mRoot;					// Ra�z de Ogre
	Ogre::FileSystemLayer* mFSLayer;	// Abstracci�n del s. de ficheros
	Ogre::OverlaySystem* mOverlaySystem;// Sistema de Overlay: requerido por OverlayManager (encargado de UI)

	bool exitRequest;					// Petici�n de salida
};
