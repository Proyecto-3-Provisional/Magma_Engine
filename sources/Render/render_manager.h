#pragma once

#include <EC/vector3D.h>
#include <singleton.h>

#include <Render/render_manager_context.h>
#include <Render/graphical_object.h>

namespace magma_engine
{
	class RenderManager : public RenderManagerContext, public Singleton<RenderManager>
	{
		// Permiso para construir
		friend Singleton<RenderManager>;
	protected:
		explicit RenderManager(bool grabCursor);
		explicit RenderManager(bool grabCursor, uint32_t w, uint32_t h,
			bool fScr, bool vSyn, int fsaa, bool gamm);
	public:
		virtual ~RenderManager();

		// Crear y destruir cámara
		void createCam(GraphicalObject* follow, const Vector3D& startPos = Vector3D(0, 0, 1000));
		void destroyCam();

		// Establecer transformación de cámara
		void setCamPos(const Vector3D& vec);
		void translateCam(const Vector3D& vec);
		void setCamOrientation(float ang, const Vector3D& axis);
		void yawCam(float deg);
		void pitchCam(float deg);
		void rollCam(float deg);

		// Establecer mirada de la cámara
		void setCamLookAt(const Vector3D& vec, const Vector3D& lDirVec = Vector3D(0, 0, -1));

		// ¿Visualizar alambres de mallas?
		void objectShowMode(unsigned int val);

		// Crear objeto
		GraphicalObject* addObject(std::string key, GraphicalObject* parent = nullptr,
			std::string mesh = "", std::string material = "default");

		// Obtener objeto
		GraphicalObject* getObject(std::string key);

		// Destruir objeto
		bool removeObject(GraphicalObject* gO);
		bool removeObject(std::string key);

		// Marcar objeto para destrucción segura (control de cuándo)
		void sunsetObject(GraphicalObject* gO);
		bool sunsetObject(std::string key);

		// Destruir todos los objetos (asegurarse al final)
		void removeObjects();

		// Destruir aquellos objetos que fueron marcados previamente
		int refreshObjects();

		// Obtener número de objetos
		int getNumObjects();
		// Obtener número de objetos marcados para borrar
		int getNumObjectsToRemove();

		// Cambiar fondo
		void setBgColor(float r, float g, float b);

		// Hacer avanzar las animaciones de los Objetos
		void stepAnimations(int deltaTime);

	protected:
		// Objetos nuestros del mundo gráfico
		std::unordered_map<std::string, GraphicalObject*> sceneObjects;
		std::list<GraphicalObject*> sceneObjectsToRemove;

		// Preparar
		virtual void setup();

		// Cerrar
		virtual void shutdown();

		// Crear malla por código: plano
		void createPlaneMesh(Ogre::String name = "mPlane1080x800");

		// Destruir cámara y volverla a crear con configuración básica
		void replaceCam();

		// Color de fondo del puerto de vista
		float bgColR;
		float bgColG;
		float bgColB;

		// Punteros
		Ogre::SceneManager* mSM = nullptr;
		Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* cameraNode = nullptr;
		Ogre::Viewport* cameraViewport = nullptr;
		GraphicalObject* cameraFollows = nullptr;

	private:
		// Colores de tripulantes
#define NUM_CREWMATES 16
		const Ogre::String crew_colors[NUM_CREWMATES]
		{
			"amongus_red",
			"amongus_brown",
			"amongus_orange",
			"amongus_yellow",
			"amongus_lime",
			"amongus_green",
			"amongus_aqua",
			"amongus_cyan",
			"amongus_blue",
			"amongus_purple",
			"amongus_magenta",
			"amongus_pink",
			"amongus_white",
			"amongus_grey_light",
			"amongus_grey_dark",
			"amongus_black"
		};
	};

}

