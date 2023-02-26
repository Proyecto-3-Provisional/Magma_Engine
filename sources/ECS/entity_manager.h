#pragma once

#include <vector>

#include "component.h"
#include "entity.h"
#include "ecs.h"
#include "messages.h"
#include "system.h"

namespace ecs {
	class EntityManager {
	public:
		EntityManager(){};
		virtual ~EntityManager(){};

		// Adding an entity simply creates an instance of Entity, adds
		// it to the list of the given group and returns it to the caller.
		template<typename T = _grp_GENERAL>
		Entity* addEntity() {

			constexpr auto gId = grpId<T>;

			// create and initialize the entity
			auto e = new Entity(gId);
			e->alive_ = true;

			// add the entity 'e' to list of entities of the given group
			//
			// IMPORTANT NOTE:
			//
			// Currently we immediately add the entity to the list of entities,
			// so we will actually see them in this 'frame' if we traverse the list of
			// entities afterwards!
			//
			// A better solution would be to add them to an auxiliary list, and
			// define a method 'flush()' that moves them from the auxiliary list
			// to the corresponding list of entities.
			//
			// We will have to call 'flush()' in each iteration of the
			// main loop. This way we guarantee that entities that are added in one
			// 'frame' they will appear only in the next 'frame' -- I leave it as an
			// exercise for you ... it could be incorporated in 'refresh' as well.
			entsByGroup_[gId].push_back(e);

			// return it to the caller
			return e;
		}

		// Setting the state of entity 'e' (alive or dead)
		inline void setAlive(Entity* e, bool alive) {
			e->alive_ = alive;
		}

		// Returns the state of the entity 'e' (alive o dead)
		inline bool isAlive(Entity* e) {
			return e->alive_;
		}

		// Adds a component to the entity 'e'. It receives the type
		// T (to be created), and the list of arguments (if any) to
		// be passed to the constructor. The component identifier
		// 'cId' is cmpId<T>.
		template<typename T, typename ...Ts>
		T* addComponent(Entity* e, Ts &&... args) {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < maxComponentId);

			// delete the current component, if any
			removeComponent<T>(e);

			// create, initialize and install the new component
			Component* c = new T(std::forward<Ts>(args)...);
			c->setContext(e, this);
			c->initComponent();
			e->cmps_[cId] = c;
			e->currCmps_.push_back(c);

			// return it to the user so i can be initialized if needed
			return static_cast<T*>(c);
		}

		// Removes the component of Entity 'e' at position T::id.
		template<typename T>
		void removeComponent(Entity* e) {

			constexpr cmpId_type cId = cmpId<T>; //T::id;
			assert(cId < maxComponentId);

			if (e->cmps_[cId] != nullptr) {

				// find the element that is equal to e->cmps_[cId] (returns an iterator)
				auto iter = std::find(e->currCmps_.begin(), e->currCmps_.end(),
					e->cmps_[cId]);

				// must have such a component
				assert(iter != e->currCmps_.end());

				// and then remove it
				e->currCmps_.erase(iter);

				// destroy it
				delete e->cmps_[cId];

				// remove the pointer
				e->cmps_[cId] = nullptr;
			}
		}

		// Returns a pointer to the component T of entity 'e'.
		template<typename T>
		inline T* getComponent(Entity* e) {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < maxComponentId);

			return static_cast<T*>(e->cmps_[cId]);
		}

		// Returns true if entity 'e' has a component T
		template<typename T>
		inline bool hasComponent(Entity* e) {

			constexpr cmpId_type cId = cmpId<T>;
			assert(cId < maxComponentId);

			return e->cmps_[cId] != nullptr;
		}

		void refresh();
		void update();
		void render();

		std::array<std::vector<Entity*>, maxGroupId> returnEntsByGroup();

		// Returns the group of entity 'e'
		//
		inline grpId_type groupId(Entity* e) {
			return e->gId_;
		}

		// Returns the vector of all entities of group T
		//
		template<typename T = _grp_GENERAL>
		inline const auto& getEntities() {
			constexpr auto gId = grpId<T>;
			return entsByGroup_[gId];
		}


	private:
		std::vector<Entity*> ents_;
		std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;

		std::vector<Message> msgs_;
		std::vector<Message> msgs_aux_;
	};

}
