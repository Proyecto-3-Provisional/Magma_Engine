#include "component.h"

void ecs::Component::setContext(Entity* ent_, EntityManager* mngr_)
{
	ent = ent_;
	mngr = mngr_;
}

void ecs::Component::setEnable(bool set_)
{
	enable = set_;
	if (set_)
		onEnable();
	else
		onDisable();
}