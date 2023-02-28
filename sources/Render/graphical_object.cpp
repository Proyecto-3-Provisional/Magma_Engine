#include "graphical_object.h"

#include "OgreRoot.h"
#include "OgreEntity.h"

GraphicalObject::GraphicalObject(Ogre::String name, Ogre::SceneManager& mSM,
	GraphicalObject* parent = nullptr, std::string mesh = "",
	std::string material = "default") : keyName(name), mySceneManager(mSM),
	parentObject(parent), childrenUsing(0), meshFile(mesh),
	materialName(material), visible(true), showsBox(false)
{
	// crear nodo como hijo de otro, o del nodo raíz
	if (parentObject)
	{
		objectNode = parentObject->getNode()->createChildSceneNode();
		parentObject->aknowledgeChild();
	}
	else
	{
		objectNode = mySceneManager.getRootSceneNode()->createChildSceneNode();
	}
	assert(objectNode);

	// determinar tipo de Objeto
	if (meshFile != "") {
		if (meshFile == "SUN")
		{
			light = mySceneManager.createLight();
			light->setType(Ogre::Light::LT_DIRECTIONAL);
			light->setDiffuseColour(0.90, 0.90, 0.90);
			objectNode->attachObject(light);
			assert(light);
			assert(!entity);
		}
		else if (meshFile == "LIGHTBULB")
		{
			light = mySceneManager.createLight();
			light->setType(Ogre::Light::LT_POINT);
			light->setDiffuseColour(0.90, 0.90, 0.90);
			objectNode->attachObject(light);
			assert(light);
			assert(!entity);
		}
		else if (meshFile == "SPOTLIGHT")
		{
			light = mySceneManager.createLight();
			light->setType(Ogre::Light::LT_SPOTLIGHT);
			light->setDiffuseColour(0.90, 0.90, 0.90);
			light->setSpotlightInnerAngle(Ogre::Degree(5.0f));	//
			light->setSpotlightOuterAngle(Ogre::Degree(90.0f));	//
			light->setSpotlightFalloff(2.0f);					//
			objectNode->attachObject(light);
			assert(light);
			assert(!entity);
		}
		else // crear entidad con su material y anclarla
		{
			entity = mySceneManager.createEntity(meshFile);
			entity->setMaterialName(materialName);
			objectNode->attachObject(entity);
			assert(entity);
			assert(!light);
		}
	}
}

GraphicalObject::~GraphicalObject()
{
	// si no es un objeto vacío, borrar su entidad (o luz)
	if (entity)
	{
		objectNode->detachObject(entity);
		mySceneManager.destroyEntity(entity);
		entity = nullptr;
	}

	if (light)
	{
		objectNode->detachObject(light);
		mySceneManager.destroyEntity(light);
		light = nullptr;
	}

	// notificar destrucción al padre
	if (parentObject)
	{
		parentObject->childRemoved();
	}

	// destruir el nodo
	mySceneManager.destroySceneNode(objectNode);
	objectNode = nullptr;
}

void GraphicalObject::translate(Ogre::Vector3 vec, Ogre::Node::TransformSpace relTo)
{
	objectNode->translate(vec, relTo);
}

void GraphicalObject::setPosition(Ogre::Vector3 vec)
{
	objectNode->setPosition(vec);
}

void GraphicalObject::setDirection(Ogre::Vector3 vec)
{
	objectNode->setDirection(vec.normalisedCopy());
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

void GraphicalObject::setOrientation(float ang, Ogre::Vector3 axis)
{
	Ogre::Quaternion q = Ogre::Quaternion(Ogre::Degree(ang), Ogre::Vector3(axis));
	objectNode->setOrientation(q);
}

void GraphicalObject::scale(float factor)
{
	objectNode->scale(factor, factor, factor);
}

void GraphicalObject::setScale(float factor)
{
	objectNode->setScale(factor, factor, factor);
}

void GraphicalObject::scale(Ogre::Vector3 factor)
{
	objectNode->scale(factor);
}

void GraphicalObject::setScale(Ogre::Vector3 factor)
{
	objectNode->setScale(factor);
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

Ogre::String GraphicalObject::getKeyName()
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
