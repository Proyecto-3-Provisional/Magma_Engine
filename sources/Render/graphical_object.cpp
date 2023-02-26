#include "graphical_object.h"

#include "OgreRoot.h"
//#include "OgreSceneNode.h"
#include "OgreEntity.h"

GraphicalObject::GraphicalObject(Ogre::String name, Ogre::SceneManager& mSM,
	GraphicalObject* parent = nullptr,
	std::string mesh = "", std::string material = "default")
	: keyName(name), mySceneManager(mSM), parentObject(parent), childrenUsing(0),
	meshFile(mesh), materialName(material), visible(true), showsBox(false)
{
	if (parentObject)
	{
		// crear nodo como hijo de otro
		objectNode = parentObject->getNode()->createChildSceneNode();
		parentObject->aknowledgeChild();
	}
	else
	{
		// crear nodo, hijo del 'raíz'
		objectNode = mySceneManager.getRootSceneNode()->createChildSceneNode();
	}

	assert(objectNode);

	if (meshFile != "") {
		// crear entidad
		entity = mySceneManager.createEntity(meshFile);

		// definir su material
		entity->setMaterialName(materialName);

		// anclar entidad a nodo
		objectNode->attachObject(entity);

		assert(entity);
	}
}

GraphicalObject::~GraphicalObject()
{
	if (entity) // si no es un objeto vacío, borrar su entidad
	{
		objectNode->detachObject(entity);
		mySceneManager.destroyEntity(entity);
		entity = nullptr;
	}

	if (parentObject)
	{
		parentObject->childRemoved();
	}

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
