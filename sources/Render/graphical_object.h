#pragma once
#include <string>
#include <OgreAutoParamDataSource.h>

// Wrapper del uso b�sico de SceneNode (y Entity) de la escena de Ogre
// Permite crear y manipular f�cilmente desde fuera objetos del mundo gr�fico

namespace Ogre
{
	class SceneNode;
	class Entity;
};

class GraphicalObject {
public:
	GraphicalObject(Ogre::String name, Ogre::SceneManager& mSM,
		GraphicalObject* parent, std::string mesh, std::string material);
	~GraphicalObject();

	// Transformaciones

	void translate(Ogre::Vector3 vec, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_PARENT);
	void setPosition(Ogre::Vector3 vec);

	void yaw(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
	void pitch(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
	void roll(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
	void setOrientation(float ang, Ogre::Vector3 axis);

	void scale(float factor);
	void setScale(float factor);

	void scale(Ogre::Vector3 factor);
	void setScale(Ogre::Vector3 factor);

	// Visibilidad

	void setMaterial(std::string matName);
	void makeVisible(bool show);
	void showDebugBox(bool show);

	// Acerca del nodo
	Ogre::String getKeyName();
	Ogre::SceneNode* getNode();
	int getChildrenUsing();

protected:
	// Notificar existencia de objetos hijos
	void aknowledgeChild();
	void childRemoved();

	// Nodo y entidad asociados a este constructo
	Ogre::SceneNode* objectNode = nullptr;
	Ogre::Entity* entity = nullptr; // nullptr -> nodo vac�o

	// Padres e hijos
	GraphicalObject* parentObject = nullptr;
	int childrenUsing;

private:
	// Gestor de la escena
	Ogre::SceneManager& mySceneManager;

	// Estado
	std::string keyName;
	std::string meshFile;
	std::string materialName;
	bool visible;
	bool showsBox;
};