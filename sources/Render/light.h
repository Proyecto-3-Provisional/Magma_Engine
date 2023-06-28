#pragma once

#include <EC/component.h>
#include <EC/vector3D.h>
#include <string>

namespace Ogre
{
	class Light;
	class SceneNode;
}

namespace magma_engine 
{
	enum LightType
	{
		DIRECTIONAL, POINT, SPOTLIGHT
	};

	LightType convertLightType(const std::string& str);

	class Light : public Component
	{
	public:
		Light();
		virtual ~Light();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();

		void setLightColor(float r, float g, float b);

	private:
		Vector3D diffuseColor; // Color
		LightType lightType; // Tipo de luz
		float innerAngle;
		float outerAngle;
		float falloff;

		Ogre::Light* light = nullptr;
		Ogre::SceneNode* sceneNode = nullptr;
	};
}
