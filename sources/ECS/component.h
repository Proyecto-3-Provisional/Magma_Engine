// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class Entity;
class EntityManager;

struct Component {
public:
	Component() : ent_(), mngr_() {}
	virtual ~Component() { }
	void setContext(Entity* ent, EntityManager* mngr);
	virtual void initComponent() { }
	virtual void update() { }
	virtual void render() { }
protected:
	Entity* ent_;
	EntityManager* mngr_;
};
