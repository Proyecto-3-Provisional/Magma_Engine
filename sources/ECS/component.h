// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

class Entity;
class Manager;

namespace magma {

struct Component {
	public:
		Component() : ent_(), mngr_() {}
		virtual ~Component() { }
		inline void setContext(Entity* ent, Manager* mngr) {
			ent_ = ent;
			mngr_ = mngr;
		}
		virtual void initComponent() { }
		virtual void update() { }
		virtual void render() { }
	protected:
		Entity* ent_;
		Manager* mngr_;
	};

}