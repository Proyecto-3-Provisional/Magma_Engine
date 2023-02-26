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

	//Entity* EntityManager::addEntity() {
	//	Entity* e = new Entity();
	//	e->setAlive(true);
	//	e->setContext(this);
	//	ents_.push_back(e);
	//	return e;
	//}

	//void EntityManager::refresh() {
	//	ents_.erase(
	//		std::remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
	//			if (e->isAlive()) {
	//				return false;
	//			}
	//			else {
	//				delete e;
	//				return true;
	//			}
	//			}), //
	//		ents_.end());
	//}

	void EntityManager::refresh()
	{
		// remove dead entities from the groups lists, and also those
	// do not belong to the group anymore
		for (ecs::grpId_type gId = 0; gId < ecs::maxGroupId; gId++) {
			auto& groupEntities = entsByGroup_[gId];
			groupEntities.erase(
				std::remove_if(groupEntities.begin(), groupEntities.end(),
					[](Entity* e) {
						if (e->alive_) {
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
		//auto n = ents_.size();
		auto n = entsByGroup_[0].size();
		for (auto i = 0u; i < n; i++)
			entsByGroup_[0][i]->update();
	}

	void EntityManager::render() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++){}
			//ents_[i]->render();
	}

	std::array<std::vector<Entity*>, maxGroupId> EntityManager::returnEntsByGroup()
	{
		return entsByGroup_;
	}

}