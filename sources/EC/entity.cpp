#include <EC/entity.h>
#include <EC/component.h>

namespace magma_engine
{
	namespace ec {
		Entity::Entity() : cmps(), alive() {}

		Entity::~Entity() {
			for (auto it = cmps.begin(); it != cmps.end(); ++it) delete it->second;
		}

		void Entity::setAlive(bool alive_)
		{
			alive = alive_;
		}

		void Entity::update(float deltaTime) {
			for (auto it = cmps.begin(); it != cmps.end(); ++it)  it->second->update(deltaTime);
		}

		void Entity::render() {
			for (auto it = cmps.begin(); it != cmps.end(); ++it)  it->second->render();
		}

		// por ahora no tenemos flush de mensajes implementado, dejar elay a false
		void Entity::send(const Message& m, bool delay) {
			if (!delay) {
				for (auto it = cmps.begin(); it != cmps.end(); ++it)  it->second->recieve(m);
			}
			else {
				msgs_.emplace_back(m);
			}
		}

		std::vector<Component*> Entity::getAllCmps() {
			std::vector<Component*> c;
			for (auto it = cmps.begin(); it != cmps.end(); ++it)  c.push_back(it->second);
			return c;
		}
	}
}

