// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class Entity;
class Manager;

struct Component {
	Component() : ent(), mngr() { }
	virtual ~Component() { }
	inline void setContext(Entity* ent, Manager* mngr) {
		ent = ent;
		mngr = mngr;
	}

	virtual void initComponent() { }
	//virtual void update() { }
	//virtual void render() { }

protected:
	Entity* ent;
	Manager* mngr;
};