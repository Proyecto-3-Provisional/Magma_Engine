#include "component.h"

void Component::setContext(Entity* ent, EntityManager* mngr) {
	ent_ = ent;
	mngr_ = mngr;
}