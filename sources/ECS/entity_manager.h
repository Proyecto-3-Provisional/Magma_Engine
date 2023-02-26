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
			e->setAlive(true);
			e->setContext(this);

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

		void refresh();
		void update();
		void render();

		std::array<std::vector<Entity*>, maxGroupId> returnEntsByGroup();


		// Returns the vector of all entities of group T
		//
		template<typename T = _grp_GENERAL>
		inline const auto& getEntities() {
			constexpr auto gId = grpId<T>;
			return entsByGroup_[gId];
		}


	private:
		//std::vector<Entity*> ents_;
		std::array<std::vector<Entity*>, maxGroupId> entsByGroup_;

		std::vector<Message> msgs_;
		std::vector<Message> msgs_aux_;
	};

}
