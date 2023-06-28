#include <Render/camera.h>

#include <iostream>
#include <Render/render_manager.h>

namespace magma_engine
{
	Camera::Camera() : Component(), showModeValue(0), pitch(0.0f), yaw(0.0f), roll(0.0f)
	{

	}

	Camera::~Camera() 
	{
		
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
		
		RenderManager::instance()->objectShowMode(showModeValue);

		if (pitch != 0.0f)
			RenderManager::instance()->pitchCam(pitch);
			
		if (yaw != 0.0f)
			RenderManager::instance()->yawCam(yaw);
			
		if (roll != 0.0f)
			RenderManager::instance()->rollCam(roll);
			
		return true;
	}

}