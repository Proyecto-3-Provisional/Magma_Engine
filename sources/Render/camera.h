#pragma once
#include <EC/component.h>

namespace magma_engine 
{

	class Camera : public Component
	{
	public:
		Camera();
		virtual ~Camera();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();

	protected:

		unsigned int showModeValue = 0;

		float pitch = 0.0f;
		float yaw = 0.0f;
		float roll = 0.0f;
	};
}