#pragma once

#include <EC/vector3D.h>

#include <OgreNode.h>

// Envoltorio para el uso básico de SceneNode, Entity y Light de Ogre.
// Permite crear y manipular fácilmente desde fuera objetos del mundo gráfico.
// Se pueden enparentar estos objetos, pero cuidado: si un objeto tiene hijos,
// se negrará a ser borrado.
// Para cada objeto se crea un nodo que puede contener una entidad, uno
// de los 3 tipos de luz, un emisor de partículas o nada...

namespace magma_engine
{
	class GraphicalObject {
	public:
		GraphicalObject(std::string name, Ogre::SceneManager& mSM,
			GraphicalObject* parent = nullptr,
			std::string mesh = "", std::string material = "default");
		~GraphicalObject();

		// Transformaciones
		void translate(const Vector3D& vec, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_PARENT);
		void setPosition(const Vector3D& vec);
		void setDirection(const Vector3D& vec);
		void yaw(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
		void pitch(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
		void roll(float deg, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_LOCAL);
		void setOrientation(float ang, const Vector3D& axis);
		void setOriLookingAt(const Vector3D& target, Ogre::Node::TransformSpace relTo = Ogre::Node::TransformSpace::TS_WORLD, const Vector3D& lDirVec = Vector3D(0, 0, -1));
		void scale(float factor);
		void setScale(float factor);

		void setScaleX(float factor);
		void setScaleY(float factor);
		void setScaleZ(float factor);

		void scale(const Vector3D& factor);
		void setScale(const Vector3D& factor);

		// Visibilidad
		void setMaterial(std::string matName);
		void makeVisible(bool show);
		void showDebugBox(bool show);

		// Luces
		void setLightColor(float r, float g, float b);

		// Emisores de part.
		void setEmitting(bool b);

		// Acerca del nodo
		std::string getKeyName();
		Ogre::SceneNode* getNode();
		int getChildrenUsing();

		// ¿La cámara le sigue?
		void setCamAttached(bool val);
		bool isCamAttached();

		// Acerca de la entidad
		bool isTrueEntity();

		// Posible animación
		bool isEntityAnimated();
		void setAnimation(std::string animName, bool startRightAway = false);
		void stepAnimation(float deltaTime);
		void animationSetEnabled(bool val);
		void animationSetLooping(bool val);

		// Malla
		Vector3D getMeshProportions();

	protected:
		// Notificar existencia de objetos hijos
		void aknowledgeChild();
		void childRemoved();

		// Nodo (y entidad/luz/part.) asociado a este constructo
		Ogre::SceneNode* objectNode = nullptr;
		// Cosas que pueden ser (si todas = nullptr -> nodo vacío)
		Ogre::Entity* entity = nullptr;
		Ogre::Light* light = nullptr;
		Ogre::ParticleSystem* particleSystem = nullptr;

		// Animación para la entidad
		Ogre::AnimationState* entityAnimation = nullptr;

		// Padres e hijos
		GraphicalObject* parentObject = nullptr;
		int childrenUsing;
		bool camAttached;

	private:
		// Gestor de la escena
		Ogre::SceneManager& mySceneManager;

		// Estado
		std::string keyName;
		std::string meshFile;
		std::string materialName;
		bool visible;
		bool showsBox;

		// Dimensiones de la malla
		Vector3D meshProportions;
	};
}

