#include <Render/graphical_object.h>

#include <iostream>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreParticleSystem.h>

namespace magma_engine
{
	GraphicalObject::GraphicalObject(std::string name, Ogre::SceneManager& mSM,
		GraphicalObject* parent, std::string mesh, std::string material)
		: keyName(name), mySceneManager(mSM), parentObject(parent), childrenUsing(0),
		camAttached(false), meshFile(mesh), materialName(material),
		visible(true), showsBox(false), meshProportions({1, 1, 1})
	{
		if (parentObject)
		{
			objectNode = parentObject->getNode()->createChildSceneNode();
			parentObject->aknowledgeChild();
		}
		else
		{
			objectNode = mySceneManager.getRootSceneNode()->createChildSceneNode();
		}

		if (meshFile != "") {
			if (meshFile == "SUN")
			{
				light = mySceneManager.createLight();
				light->setType(Ogre::Light::LT_DIRECTIONAL);
				light->setDiffuseColour(0.90f, 0.90f, 0.90f);
				objectNode->attachObject(light);
			}
			else if (meshFile == "LIGHTBULB")
			{
				light = mySceneManager.createLight();
				light->setType(Ogre::Light::LT_POINT);
				light->setDiffuseColour(0.90f, 0.90f, 0.90f);
				objectNode->attachObject(light);
			}
			else if (meshFile == "SPOTLIGHT")
			{
				light = mySceneManager.createLight();
				light->setType(Ogre::Light::LT_SPOTLIGHT);
				light->setDiffuseColour(0.90f, 0.90f, 0.90f);
				light->setSpotlightInnerAngle(Ogre::Degree(5.0f));	//
				light->setSpotlightOuterAngle(Ogre::Degree(90.0f));	//
				light->setSpotlightFalloff(2.0f);					//
				objectNode->attachObject(light);
			}
			else if (meshFile == "EMITTER") {
				Ogre::String partSysName = "ps_" + keyName;
				particleSystem = mySceneManager.createParticleSystem(partSysName, materialName);
				particleSystem->setEmitting(true);
				objectNode->attachObject(particleSystem);
			}
			else
			{
				entity = mySceneManager.createEntity(meshFile);
				entity->setMaterialName(materialName);
				objectNode->attachObject(entity);
				Ogre::Vector3 size = entity->getBoundingBox().getSize();
				meshProportions = Vector3D({ size.x, size.y, size.z });
			}
		}
	}

	// 1. Si no es un objeto vacío, borrar su entidad/luz/emisor
	// 2. Notificar destrucción al padre
	// 3. Destruir el nodo
	GraphicalObject::~GraphicalObject()
	{
		if (entity)
		{
			objectNode->detachObject(entity);
			mySceneManager.destroyEntity(entity);
			entity = nullptr;
		}
		if (light)
		{
			objectNode->detachObject(light);
			mySceneManager.destroyLight(light);
			light = nullptr;
		}
		if (particleSystem) {
			objectNode->detachObject(particleSystem);
			mySceneManager.destroyParticleSystem(particleSystem);
			particleSystem = nullptr;
		}

		if (parentObject)
			parentObject->childRemoved();

		mySceneManager.destroySceneNode(objectNode);
		objectNode = nullptr;
	}

	void GraphicalObject::translate(const Vector3D& vec, Ogre::Node::TransformSpace relTo)
	{
		objectNode->translate(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()), relTo);
	}

	void GraphicalObject::setPosition(const Vector3D& vec)
	{
		objectNode->setPosition(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()));
	}

	// Útil en luces direccionales
	void GraphicalObject::setDirection(const Vector3D& vec)
	{
		objectNode->setDirection(Ogre::Vector3(vec.getX(), vec.getY(), vec.getZ()).normalisedCopy(),
			Ogre::Node::TS_PARENT, Ogre::VectorBase<3, Ogre::Real>::UNIT_X);
	}

	void GraphicalObject::yaw(float deg, Ogre::Node::TransformSpace relTo)
	{
		objectNode->yaw(Ogre::Degree(deg), relTo);
	}

	void GraphicalObject::pitch(float deg, Ogre::Node::TransformSpace relTo)
	{
		objectNode->pitch(Ogre::Degree(deg), relTo);
	}

	void GraphicalObject::roll(float deg, Ogre::Node::TransformSpace relTo)
	{
		objectNode->roll(Ogre::Degree(deg), relTo);
	}

	void GraphicalObject::setOrientation(float ang, const Vector3D& axis)
	{
		Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(ang), Ogre::Vector3(axis.getX(), axis.getY(), axis.getZ()));
		objectNode->setOrientation(q);
	}

	void GraphicalObject::setOriLookingAt(const Vector3D& target,
		Ogre::Node::TransformSpace relTo, const Vector3D& lDirVec)
	{
		objectNode->lookAt(Ogre::Vector3(target.getX(), target.getY(), target.getZ()), relTo,
			Ogre::Vector3(lDirVec.getX(), lDirVec.getY(), lDirVec.getZ()));
	}

	void GraphicalObject::scale(float factor)
	{
		objectNode->scale(factor, factor, factor);
	}

	void GraphicalObject::setScale(float factor)
	{
		objectNode->setScale(factor, factor, factor);
	}

	void GraphicalObject::setScaleX(float factor)
	{
		objectNode->setScale(factor, objectNode->getScale().y, objectNode->getScale().z);
	}

	void GraphicalObject::setScaleY(float factor)
	{
		objectNode->setScale(objectNode->getScale().x, factor, objectNode->getScale().z);
	}

	void GraphicalObject::setScaleZ(float factor)
	{
		objectNode->setScale(objectNode->getScale().x, objectNode->getScale().y, factor);
	}

	void GraphicalObject::scale(const Vector3D& factor)
	{
		objectNode->scale(Ogre::Vector3(factor.getX(), factor.getY(), factor.getZ()));
	}

	void GraphicalObject::setScale(const Vector3D& factor)
	{
		objectNode->setScale(Ogre::Vector3(factor.getX(), factor.getY(), factor.getZ()));
	}

	void GraphicalObject::setMaterial(std::string matName)
	{
		materialName = matName;
		if (entity)
			entity->setMaterialName(matName);
	}

	void GraphicalObject::makeVisible(bool show)
	{
		visible = show;
		objectNode->setVisible(show);
	}

	void GraphicalObject::showDebugBox(bool show)
	{
		showsBox = show;
		objectNode->showBoundingBox(show);
	}

	void GraphicalObject::setLightColor(float r, float g, float b)
	{
		if (light)
			light->setDiffuseColour(r, g, b);
	}

	void GraphicalObject::setEmitting(bool b)
	{
		if (particleSystem)
			particleSystem->setEmitting(b);
	}

	std::string GraphicalObject::getKeyName()
	{
		return keyName;
	}

	inline Ogre::SceneNode* GraphicalObject::getNode()
	{
		return objectNode;
	}

	void GraphicalObject::aknowledgeChild()
	{
		childrenUsing++;
	}

	void GraphicalObject::childRemoved()
	{
		childrenUsing--;
	}

	int GraphicalObject::getChildrenUsing()
	{
		return childrenUsing;
	}

	void GraphicalObject::setCamAttached(bool val)
	{
		camAttached = val;
	}

	bool GraphicalObject::isCamAttached()
	{
		return camAttached;
	}

	bool GraphicalObject::isTrueEntity()
	{
		return entity != nullptr;
	}

	bool GraphicalObject::isEntityAnimated()
	{
		return (isTrueEntity() && (entityAnimation != nullptr));
	}

	void GraphicalObject::setAnimation(std::string animName, bool startRightAway)
	{
		if (entity)
		{
			animationSetEnabled(false);
			if (animName == "")
			{
				entityAnimation = nullptr;
			}
			else
			{
				entityAnimation = entity->getAnimationState(animName);
				if (startRightAway)
					animationSetEnabled(true);
			}
		}
	}

	void GraphicalObject::stepAnimation(float deltaTime)
	{
		if (entityAnimation)
			entityAnimation->addTime(deltaTime);
	}

	void GraphicalObject::animationSetEnabled(bool val)
	{
		if (entityAnimation)
			entityAnimation->setEnabled(val);
	}

	void GraphicalObject::animationSetLooping(bool val)
	{
		if (entityAnimation)
			entityAnimation->setLoop(val);
	}

	Vector3D GraphicalObject::getMeshProportions()
	{
		return meshProportions;
	}

	Ogre::Quaternion GraphicalObject::getOrientation()
	{
		return objectNode->getOrientation();
	}
}



