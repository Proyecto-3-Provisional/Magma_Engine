#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

#include <EC/vector3D.h>
#include <singleton.h>
#include <string>
#include <list>
#include <unordered_map>

namespace Ogre {
	class SceneManager;
	class Camera;
	class SceneNode;
	class Viewport;
}

namespace magma_engine
{
	class RenderManagerContext;
	class GraphicalObject;

	class MAGMAENGINE_API RenderManager : public Singleton<RenderManager>
	{
		// Permiso para construir
		friend Singleton<RenderManager>;
	protected:
		explicit RenderManager(bool grabCursor);
		explicit RenderManager(bool grabCursor, uint32_t w, uint32_t h,
			bool fScr, bool vSyn, int fsaa, bool gamm);
	public:
		~RenderManager();

		// Crear y destruir c�mara
		void createCam(GraphicalObject* follow, const Vector3D& startPos = Vector3D(0, 0, 1000));
		void destroyCam();

		// Establecer transformaci�n de c�mara
		void setCamPos(const Vector3D& vec);
		void translateCam(const Vector3D& vec);
		void setCamOrientation(float ang, const Vector3D& axis);
		void yawCam(float deg);
		void pitchCam(float deg);
		void rollCam(float deg);

		// Establecer mirada de la c�mara
		void setCamLookAt(const Vector3D& vec, const Vector3D& lDirVec = Vector3D(0, 0, -1));

		// �Visualizar alambres de mallas?
		void objectShowMode(unsigned int val);

		// Crear objeto
		GraphicalObject* addObject(std::string key, GraphicalObject* parent = nullptr,
			std::string mesh = "", std::string material = "default");

		// Obtener objeto
		GraphicalObject* getObject(std::string key);

		// Destruir objeto
		bool removeObject(GraphicalObject* gO);
		bool removeObject(std::string key);

		// Marcar objeto para destrucci�n segura (control de cu�ndo)
		void sunsetObject(GraphicalObject* gO);
		bool sunsetObject(std::string key);

		// Destruir todos los objetos (asegurarse al final)
		void removeObjects();

		// Destruir aquellos objetos que fueron marcados previamente
		int refreshObjects();

		// Obtener n�mero de objetos
		int getNumObjects();
		// Obtener n�mero de objetos marcados para borrar
		int getNumObjectsToRemove();

		// Cambiar fondo
		void setBgColor(float r, float g, float b);

		// Hacer avanzar las animaciones de los Objetos
		void stepAnimations(int deltaTime);

		// Funciones de RenderManagerContext
		bool renderFrame();
		void notifyWindowResized();
		bool initApp();
		void closeApp();
		int getWinWidth();
		int getWinHeight();

		void makeMessageBox(const char* title, const char* message);

		Ogre::SceneManager* getSceneManager();

	protected:
		// Objetos nuestros del mundo gr�fico
		std::unordered_map<std::string, GraphicalObject*> sceneObjects;
		std::list<GraphicalObject*> sceneObjectsToRemove;

		// Cerrar
		void shutdown();

		// Destruir c�mara y volverla a crear con configuraci�n b�sica
		void replaceCam();

		// Color de fondo del puerto de vista
		float bgColR;
		float bgColG;
		float bgColB;

		// Punteros
		RenderManagerContext* context = nullptr;

		Ogre::SceneManager* mSM = nullptr;
		Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* cameraNode = nullptr;
		Ogre::Viewport* cameraViewport = nullptr;
		GraphicalObject* cameraFollows = nullptr;
	};
}

