#include <EC/entity_manager.h>
#include <EC/entity.h>
#include <EC/transform.h>

namespace ec {
	//EntityManager::EntityManager() :
	//	ents_() {
	//	ents_.reserve(100);
	//}

	// for exterior es para cada grupo, el interior es para la entidad en si
	EntityManager::~EntityManager() {
		for (auto& ents : entsByGroup) {
			for (auto e : ents)
				delete e;
		}
	}

	void EntityManager::refresh()
	{
		for (ec::grpId_type gId = 0; gId < ec::maxGroupId; gId++) {
			auto& groupEntities = entsByGroup[gId];
			groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
					[](Entity* e) {
						if (e->isAlive()) {
							return false;
						}
						else {
							delete e; e = nullptr;
							return true;
						}
					}), groupEntities.end());
		}
	}

	void EntityManager::update(float deltaTime) {
		for (auto& ents : entsByGroup) {
			auto n = ents.size();
			for (auto i = 0u; i < n; i++)
				entsByGroup[0][i]->update(deltaTime);
		}
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