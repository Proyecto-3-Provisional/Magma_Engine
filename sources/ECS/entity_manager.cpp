#include "entity_manager.h"

#include "entity.h"

namespace magma {

	EntityManager::EntityManager() :
		ents_() {
		ents_.reserve(100);
	}

	EntityManager::~EntityManager() {
		for (auto e : ents_)
			delete e;
	}

	Entity* EntityManager::addEntity() {
		Entity* e = new Entity();
		e->setAlive(true);
		e->setContext(this);
		ents_.push_back(e);
		return e;
	}

	void EntityManager::refresh() {
		ents_.erase(
			std::remove_if(ents_.begin(), ents_.end(), [](Entity* e) {
				if (e->isAlive()) {
					return false;
				}
				else {
					delete e;
					return true;
				}
				}), //
			ents_.end());
	}

	void EntityManager::update() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->update();
	}

	void EntityManager::render() {
		auto n = ents_.size();
		for (auto i = 0u; i < n; i++)
			ents_[i]->render();
	}
}
