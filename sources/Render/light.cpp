#include "light.h"

#include <iostream>
#include <singleton.h>
#include <Render/render_manager.h>
#include <Render/graphical_object.h>
#include <OgreSceneManager.h>

namespace magma_engine
{
	LightType convertLightType(const std::string& str) 
	{
		if (str == "DIRECTIONAL") return DIRECTIONAL;
		else if (str == "POINT") return POINT;
		else if (str == "SPOTLIGHT") return SPOTLIGHT;
		else std::cout << "WARNING! - tipo de luz especificado incorrectamente\n\n";
	}

	Light::Light() : Component(), diffuseColor(), lightType(), innerAngle(), outerAngle(), falloff() {}

	Light::~Light() 
	{
		if (light)
		{
			sceneNode->detachObject(light);
			magma_engine::RenderManager::instance()->getSceneManager()->destroyLight(light);
			light = nullptr;
			sceneNode = nullptr;
		}
	}

	bool Light::initComponent(std::map<std::string, std::string> args)
	{
		try
		{
			Vector3D lightColor = Vector3D(
				stof(args["diffuseColorX"]),
				stof(args["diffuseColorY"]),
				stof(args["diffuseColorZ"])
			);
			diffuseColor = lightColor;

			lightType = convertLightType(args["lightType"]);

			innerAngle = stof(args["innerAngle"]);
			outerAngle = stof(args["outerAngle"]);
			falloff = stof(args["falloff"]);
		}
		catch (std::exception& e)
		{
			std::cout << "WARNING! - error en un componente Light \n \n      " << e.what();
			return false;
		}

		return true;
	}

	bool Light::start() 
	{
		sceneNode = magma_engine::RenderManager::instance()->getSceneManager()->getRootSceneNode();
		light = magma_engine::RenderManager::instance()->getSceneManager()->createLight();

		if (sceneNode == nullptr || light == nullptr)
		{
			std::cout << "WARNING! - error al cargar luz \n\n";
			return false;
		}

		switch (lightType)
		{
		case DIRECTIONAL: 
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDiffuseColour(diffuseColor.getX(), diffuseColor.getY(), diffuseColor.getZ());
			sceneNode->attachObject(light);
			break;
		case POINT:
			light->setType(Ogre::Light::LT_POINT);
			light->setDiffuseColour(diffuseColor.getX(), diffuseColor.getY(), diffuseColor.getZ());
			sceneNode->attachObject(light);
			break;
		case SPOTLIGHT:
			light->setType(Ogre::Light::LT_SPOTLIGHT);
			light->setDiffuseColour(diffuseColor.getX(), diffuseColor.getY(), diffuseColor.getZ());
			light->setSpotlightInnerAngle(Ogre::Degree(innerAngle));
			light->setSpotlightOuterAngle(Ogre::Degree(outerAngle));
			light->setSpotlightFalloff(falloff);
			sceneNode->attachObject(light);
			break;
		default: break;
		}

		return true;
	}

	void Light::setLightColor(float r, float g, float b) 
	{
		if (light)
			light->setDiffuseColour(r, g, b);
	}
}