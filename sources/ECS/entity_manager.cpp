#include "entity_manager.h"

#include "entity.h"
#include "transform.h"

namespace ecs {
	//EntityManager::EntityManager() :
	//	ents_() {
	//	ents_.reserve(100);
	//}

	//EntityManager::~EntityManager() {
	//	for (auto e : ents_)
	//		delete e;
	//}

	void EntityManager::refresh()
	{
		for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
			auto& groupEntities = entsByGroup[gId];
			groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
					[](Entity* e) {
						if (e->isAlive()) {
							return false;
						}
						else {
							delete e;
							return true;
						}
					}), groupEntities.end());
		}
	}

	void EntityManager::update() {
		auto n = entsByGroup[0].size();
		for (auto i = 0u; i < n; i++)
			entsByGroup[0][i]->update();
	}

	void EntityManager::render() {
		for (auto& ents : entsByGroup) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				ents[i]->render();
		}
	}

	std::array<std::vector<Entity*>, maxGroupId> EntityManager::returnEntsByGroup()
	{
		return entsByGroup;
	}

}