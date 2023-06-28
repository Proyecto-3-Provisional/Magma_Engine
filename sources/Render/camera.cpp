#include <Render/camera.h>

//#include <singleton.h>
#include <iostream>
#include <Render/render_manager.h>
//#include <Render/render_manager_context.h>
//#include <OgreRoot.h>
//#include <OgreRenderWindow.h>
//#include <OgreViewport.h>

namespace magma_engine
{
	Camera::Camera() : Component(), showModeValue(0), pitch(0.0f), yaw(0.0f), roll(0.0f)
	{

	}

	Camera::~Camera() 
	{
		/*magma_engine::RenderManager::instance()->getRenderContext()->getRenderWindow()->removeAllViewports();
		cameraViewport = nullptr;

		cameraNode->detachObject(camera);
		magma_engine::RenderManager::instance()->getSceneManager()->destroyCamera(camera);
		camera = nullptr;

		magma_engine::RenderManager::instance()->getSceneManager()->destroySceneNode(cameraNode);
		cameraNode = nullptr;*/
	}

	bool Camera::initComponent(std::map<std::string, std::string> args)
	{
		try
		{
			Vector3D camSPos = Vector3D(
				stof(args["camPosX"]),
				stof(args["camPosY"]),
				stof(args["camPosZ"])
			);
			RenderManager::instance()->createCam(nullptr, camSPos);
			RenderManager::instance()->setCamPos(camSPos);

			Vector3D camLook = Vector3D(
				stof(args["camLookX"]),
				stof(args["camLookY"]),
				stof(args["camLookZ"])
			);
			RenderManager::instance()->setCamLookAt(camLook);

			RenderManager::instance()->setBgColor(
				stof(args["redBG"]),
				stof(args["greenBG"]),
				stof(args["blueBG"]));

			//camera = magma_engine::RenderManager::instance()->getSceneManager()->createCamera(args["cameraName"]);
			/*if (camera == nullptr)
			{
				std::cout << "WARNING! no se ha creado la camara en el initComponent \n";
				return false;
			}

			camera->setAutoAspectRatio(true);

			cameraNode = magma_engine::RenderManager::instance()->getSceneManager()->getRootSceneNode()->createChildSceneNode();
			if (cameraNode == nullptr) {
				std::cout << "WARNING! no se ha creado el cameraNode en el initComponent \n";
				magma_engine::RenderManager::instance()->getSceneManager()->destroyCamera(camera);
				camera = nullptr;
				return false;
			}*/

			//cameraNode->attachObject(camera);

			/*Vector3D camSPos = Vector3D(
				stof(args["camPosX"]),
				stof(args["camPosY"]),
				stof(args["camPosZ"])
			);*/
			//cameraNode->setPosition(Ogre::Vector3(camSPos.getX(), camSPos.getY(), camSPos.getZ()));

			/*Vector3D camLook = Vector3D(
				stof(args["camLookX"]),
				stof(args["camLookY"]),
				stof(args["camLookZ"])
			);*/
			//cameraNode->lookAt(Ogre::Vector3(camLook.getX(), camLook.getY(), camLook.getZ()), Ogre::Node::TransformSpace::TS_WORLD);
			
			/*if (stoi(args["isOrtho"]))
				camera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
			else
				camera->setProjectionType(Ogre::PT_PERSPECTIVE);*/

			//camera->setNearClipDistance(stoi(args["nearClip"]));
			//camera->setFarClipDistance(stoi(args["farClip"]));

			/*magma_engine::RenderManager::instance()->getRenderContext()->getRenderWindow()->removeAllViewports();
			cameraViewport = magma_engine::RenderManager::instance()->getRenderContext()->getRenderWindow()->addViewport(camera);
			if (cameraViewport == nullptr) 
			{
				std::cout << "WARNING! no se ha creado el viewport de la camara en el initComponent \n";
				cameraNode->detachObject(camera);
				magma_engine::RenderManager::instance()->getSceneManager()->destroyCamera(camera);
				camera = nullptr;
				magma_engine::RenderManager::instance()->getSceneManager()->destroySceneNode(cameraNode);
				cameraNode = nullptr;
				return false;
			}

			cameraViewport->setBackgroundColour(Ogre::ColourValue(
				stof(args["redBG"]),
				stof(args["greenBG"]),
				stof(args["blueBG"]))
			);*/

			showModeValue = stoi(args["showModeValue"]);

			pitch = stof(args["pitch"]);
			yaw = stof(args["yaw"]);
			roll = stof(args["roll"]);
			
		}
		catch (std::exception& e)
		{
			std::cout << "WARNING! - error en un componente Camera \n \n      " << e.what();
			return false;
		}

		return true;
	}

	bool Camera::start()
	{
		if (showModeValue > 3) {
			std::cout << "WARNING! showModeValue tiene un valor mayor que 3 \n";
			return false;
		}
		//objectShowMode(showModeValue);
		RenderManager::instance()->objectShowMode(showModeValue);

		if (pitch != 0.0f)
			RenderManager::instance()->pitchCam(pitch);
			//pitchCam(pitch);
		if (yaw != 0.0f)
			RenderManager::instance()->yawCam(yaw);
			//yawCam(yaw);
		if (roll != 0.0f)
			RenderManager::instance()->rollCam(roll);
			//rollCam(roll);

		return true;
	}

	/*void Camera::setNearClipDistance(float nClip)
	{
		camera->setNearClipDistance(nClip);
	}

	void Camera::setFarClipDistance(float nClip)
	{
		camera->setFarClipDistance(nClip);
	}

	void Camera::setCamPos(const Vector3D& vec) 
	{
		if (cameraNode)
			cameraNode->setPosition(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()));
	}

	void Camera::translateCam(const Vector3D& vec)
	{
		if (cameraNode)
			cameraNode->translate(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void Camera::setCamOrientation(float ang, const Vector3D& axis)
	{
		if (cameraNode)
		{
			Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(ang), Ogre::Vector3(axis.getX(), axis.getY(), axis.getZ()));
			cameraNode->setOrientation(q);
		}
	}

	void Camera::yawCam(float deg)
	{
		if (cameraNode)
			cameraNode->yaw(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void Camera::pitchCam(float deg)
	{
		if (cameraNode)
			cameraNode->pitch(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void Camera::rollCam(float deg)
	{
		if (cameraNode)
			cameraNode->roll(Ogre::Degree(deg), Ogre::Node::TransformSpace::TS_LOCAL);
	}

	void Camera::setCamLookAt(const Vector3D& vec, const Vector3D& lDirVec)
	{
		if (cameraNode)
			cameraNode->lookAt(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()),
				Ogre::Node::TransformSpace::TS_WORLD,
				Ogre::Vector3(lDirVec.getX(), lDirVec.getY(), lDirVec.getZ()));
	}

	void Camera::setBgColor(float r, float g, float b)
	{
		if (cameraViewport)
		{
			cameraViewport->setBackgroundColour(Ogre::ColourValue(r, g, b));
		}
	}

	void Camera::objectShowMode(unsigned int val)
	{
		if(camera)
			camera->setPolygonMode((Ogre::PolygonMode)val);
	}

	Ogre::Camera* Camera::getCamera() 
	{
		return camera;
	}

	Vector3D Camera::getCameraPos() {
		if (cameraNode)
			return { cameraNode->getPosition().x, cameraNode->getPosition().y, cameraNode->getPosition().z };
	}

	Vector3D Camera::getCameraDir() {
		if (camera)
			return { camera->getRealDirection().x, camera->getRealDirection().y, camera->getRealDirection().z };
	}*/
}