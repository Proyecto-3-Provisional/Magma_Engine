#include <Render/graphical_object.h>

#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreParticleSystem.h>

// Primero se crea el nodo de este Objeto Gráfico como hijo de otro, o
// como hijo del nodo raíz de la escena (en función de 'parent').
// Después se determina el tipo de Objeto (según la cadena 'mesh'):
//  * ""			-> nodo vacío (ignora 'mesh' y 'material')
//	* "SUN"			-> luz direccional (ignora 'mesh' y 'material')
//	* "LIGHTBULB"	-> luz puntual (ignora 'mesh' y 'material')
//	* "SPOTLIGHT"	-> foco de luz (ignora 'mesh' y 'material')
//	* "EMITTER"		-> emisor de partículas (ignora 'mesh'; 'material' indica sistema)
//	* (otra cosa)	-> entidad gráfica normal con malla determinada 'mesh'

GraphicalObject::GraphicalObject(Ogre::String name, Ogre::SceneManager& mSM,
	GraphicalObject* parent, std::string mesh, std::string material)
	: keyName(name), mySceneManager(mSM), parentObject(parent), childrenUsing(0),
	camAttached(false), meshFile(mesh), materialName(material),
	visible(true), showsBox(false)
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

void GraphicalObject::translate(Ogre::Vector3 vec, Ogre::Node::TransformSpace relTo)
{
	objectNode->translate(vec, relTo);
}

void GraphicalObject::setPosition(Ogre::Vector3 vec)
{
	objectNode->setPosition(vec);
}

// Útil en luces direccionales
void GraphicalObject::setDirection(Ogre::Vector3 vec)
{
	objectNode->setDirection(vec.normalisedCopy(), Ogre::Node::TS_PARENT, Ogre::VectorBase<3, Ogre::Real>::UNIT_X);
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

void GraphicalObject::setOriLookingAt(Ogre::Vector3 target,
	Ogre::Node::TransformSpace relTo, Ogre::Vector3 lDirVec)
{
	objectNode->lookAt(target, relTo, lDirVec);
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

void GraphicalObject::setEmitting(bool b)
{
	if (particleSystem)
		particleSystem->setEmitting(b);
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

void GraphicalObject::setAnimation(Ogre::String animName, bool startRightAway)
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
