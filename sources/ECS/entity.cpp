#include "entity.h"

#include "component.h"
#include "OgreMesh.h"

namespace ec {

	Entity::~Entity() {
		for (auto c : cmps)
			if (c != nullptr)
				delete c;
	}

	bool Entity::init(ec::grpId_type gId_)
	{
		gId = gId_;
		currCmps.reserve(ec::maxComponentId);

		return true;
	}

	void Entity::setContext(EntityManager* mngr_)
	{
		mngr = mngr_;
	}

	void Entity::setAlive(bool alive_)
	{
		alive = alive_;
	}

	void Entity::update(float deltaTime) {
		auto n = currCmps.size();
		for (auto i = 0u; i < n; i++)
			currCmps[i]->update(deltaTime);
	}

	void Entity::render() {
		auto n = currCmps.size();
		for (auto i = 0u; i < n; i++)
			currCmps[i]->render();
	}
}