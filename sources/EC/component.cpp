#include <EC/component.h>

void ec::Component::setContext(Entity* ent_, EntityManager* mngr_)
{
	ent = ent_;
	mngr = mngr_;
}

void ec::Component::setEnable(bool set_)
{
	enable = set_;
	if (set_)
		onEnable();
	else
		onDisable();
}