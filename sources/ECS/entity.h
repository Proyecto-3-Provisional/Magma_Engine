// Samir Genaim (modified to some extent or another)

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

		// Each entity knows to which manager it belongs, we use
		// this method to set the context
		//
		inline void setContext(EntityManager* mngr) {
			mngr_ = mngr;
		}

		// Setting the state of entity 'e' (alive or dead)   ****
		inline void setAlive(bool alive) {
			alive_ = alive;
		}

		// Returns the state of the entity 'e' (alive o dead)  ****
		inline bool isAlive() {
			return alive_;
		}

		// Adds a component to the entity 'e'. It receives the type     ****
		// T (to be created), and the list of arguments (if any) to
		// be passed to the constructor. The component identifier
		// 'cId' is cmpId<T>.
		template<typename T, typename ...Ts>
		T* addComponent(Ts &&... args) {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < maxComponentId);

			// delete the current component, if any
			removeComponent<T>();

			// create, initialize and install the new component
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(this, mngr_);
			c->initComponent();
			cmps_[cId] = c;
			currCmps_.push_back(c);

			// return it to the user so i can be initialized if needed
			return static_cast<T*>(c);
		}

		// Removes the component of Entity 'e' at position T::id.      ****
		template<typename T>
		void removeComponent() {

			constexpr cmpId_type cId = cmpId<T>; //T::id;
			assert(cId < maxComponentId);

			if (cmps_[cId] != nullptr) {

				// find the element that is equal to e->cmps_[cId] (returns an iterator)
				auto iter = std::find(currCmps_.begin(), currCmps_.end(),
					cmps_[cId]);

				// must have such a component
				assert(iter != currCmps_.end());

				// and then remove it
				currCmps_.erase(iter);

				// destroy it
				delete cmps_[cId];

				// remove the pointer
				cmps_[cId] = nullptr;
			}
		}

		// Returns a pointer to the component T of entity 'e'.      ****
		template<typename T>
		inline T* getComponent() {

			constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);

			return static_cast<T*>(cmps_[cId]);
		}

		// Returns true if entity 'e' has a component T        ****
		template<typename T>
		inline bool hasComponent() {

			constexpr cmpId_type cId = T::id;
			assert(cId < ecs::maxComponentId);

			return cmps_[cId] != nullptr;
		}

		// returns the entity's group 'gId'
		//
		inline ecs::grpId_type groupId() {
			return gId_;
		}

		void update();

		void render();

	private:
		//friend EntityManager;

		EntityManager* mngr_;
		std::vector<Component*> currCmps_;
		std::array<Component*, maxComponentId> cmps_;
		bool alive_;
		ecs::grpId_type gId_;

		Ogre::Entity* entOgre;
		Ogre::SceneNode* ogreNode;
	};
}
