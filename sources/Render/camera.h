#pragma once
#include <EC/component.h>
#include <EC/vector3D.h>

//namespace Ogre {
//	class Camera;
//	class Viewport;
//	class SceneNode;
//	class SceneManager;
//}

namespace magma_engine 
{
	//class GraphicalObject;

	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();

		//void setNearClipDistance(float nClip);
		//void setFarClipDistance(float fClip);

		//// Establecer transformación de cámara
		//void setCamPos(const Vector3D& vec);
		//void translateCam(const Vector3D& vec);
		//void setCamOrientation(float ang, const Vector3D& axis);
		//void yawCam(float deg);
		//void pitchCam(float deg);
		//void rollCam(float deg);

		//// Establecer mirada de la cámara
		//void setCamLookAt(const Vector3D& vec, const Vector3D& lDirVec = Vector3D(0, 0, -1));

		//// Cambiar fondo
		//void setBgColor(float r, float g, float b);

		///* Esto define como se van a renderizar los poligonos en la escena
		// PM_POINTS		1 //en este solo se renderizaran los puntos de cada poligono
		// PM_WIREFRAME	2 //en este solo se dibuja el contorno de los poligonos
		// PM_SOLID		3 //modo normal, los poligonos se rellenan
		//*/
		//void objectShowMode(unsigned int val);

		////Da el objeto camara
		//Ogre::Camera* getCamera();

		////Da la posicion de la camara
		//Vector3D getCameraPos();

		////Da la direccion a la que esta mirando la camara
		//Vector3D getCameraDir();

	protected:
		/*Ogre::Camera* camera = nullptr;
		Ogre::SceneNode* cameraNode = nullptr;
		Ogre::Viewport* cameraViewport = nullptr;*/

		unsigned int showModeValue = 0;

		float pitch = 0.0f;
		float yaw = 0.0f;
		float roll = 0.0f;
	};
}