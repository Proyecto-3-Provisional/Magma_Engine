#pragma once
#include <string>
#include <OgreAutoParamDataSource.h>

// Envoltorio para el uso básico de SceneNode, Entity y Light de Ogre
// Permite crear y manipular fácilmente desde fuera objetos del mundo gráfico

// Para cada objeto se crea un nodo que puede contener o una entidad o uno
// de los 3 tipos de luz, o nada...

// Algunos campos como "material" pueden ser ignorados

// Problemas conocidos:
// - No es tan práctico cachear objetos
// - Si un objeto tiene hijos, se negrará a ser borrado

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

	void setDirection(Ogre::Vector3 vec);

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

	// Luces
	void setLightColor(float r, float g, float b);

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
	// Cosas que pueden ser (si toas = nullptr -> nodo vacío)
	Ogre::Entity* entity = nullptr;
	Ogre::Light* light = nullptr;

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