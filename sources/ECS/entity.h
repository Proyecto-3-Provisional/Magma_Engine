// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

#include <array>
#include <vector>
#include <string>

#include "OgreEntity.h"
#include "component.h"
#include "ecs.h"

namespace ecs{

	//entity va a actuar como una coleccion de componentes
	class Entity {
	public:
		Entity(ecs::grpId_type gId);
		
		virtual ~Entity();


		// we delete the copy constructor/assignment because it is
		// not clear how to copy the components
		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		inline Ogre::Entity* getOgreEnt() { return entOgre; };
		inline Ogre::SceneNode* getOgreNode() { return ogreNode; };
		void update();

		void render();

	private:
		friend EntityManager;

		std::vector<Component*> currCmps_;
		std::array<Component*, maxComponentId> cmps_;
		bool alive_;
		ecs::grpId_type gId_;

		Ogre::Entity* entOgre;
		Ogre::SceneNode* ogreNode;
	};
}



