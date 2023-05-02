#include <EC/entity_manager.h>
#include <EC/entity.h>
#include <EC/transform.h>

namespace magma_engine
{
	EntityManager::~EntityManager() {
		for (auto& e : ents_) {
			delete e;
			e = nullptr;
		}
		ents_.clear();
	}

	void EntityManager::refresh()
	{
		auto it = ents_.begin();
		while (it != ents_.end()) {
			if (!(*it)->isAlive()) {
				delete (*it); // Borra la entidad
				it = ents_.erase(it);
			}
			else ++it;
		}
	}

	void EntityManager::update(float deltaTime) {
		for (auto& e : ents_) e->update(deltaTime);
	}

	void EntityManager::render() {
		for (auto& e : ents_) e->render();
	}
}

