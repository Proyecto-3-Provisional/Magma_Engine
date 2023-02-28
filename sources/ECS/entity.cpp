#include "entity.h"

#include "component.h"
#include "OgreMesh.h"

namespace ecs {

	Entity::Entity(ecs::grpId_type gId_, GraphicalObject* graphObj_) :
		currCmps(),
		cmps(),
		alive(),
		gId(gId_),
		graphObj(graphObj_) {
		currCmps.reserve(ecs::maxComponentId);
	}

	Entity::~Entity() {
		for (auto c : cmps)
			if (c != nullptr)
				delete c;
	}
	void Entity::setContext(EntityManager* mngr_)
	{
		mngr = mngr_;
	}

	void Entity::setAlive(bool alive_)
	{
		alive = alive_;
	}

	void Entity::update() {
		auto n = currCmps.size();
		for (auto i = 0u; i < n; i++)
			currCmps[i]->update();
	}

	void Entity::render() {
		auto n = currCmps.size();
		for (auto i = 0u; i < n; i++)
			currCmps[i]->render();
	}
}