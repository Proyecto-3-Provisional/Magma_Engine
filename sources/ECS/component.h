// This file is part of the course TPV2@UCM - Samir Genaim (modified to some extent or another)

#pragma once

#include <string>
#include "ecs.h"

namespace ecs {
	struct Component {
	public:
		Component() : ent_(), mngr_() {}
		virtual ~Component() { }
		inline void setContext(Entity* ent, EntityManager* mngr) {
			ent_ = ent;
			mngr_ = mngr;
		}
		inline bool isEnable() { return enable_; }
		inline void setEnable(bool set)
		{
			enable_ = set;
			if (set)
				onEnable();
			else
				onDisable();
		}
		virtual void initComponent() { }
		virtual void update() { }
		virtual void render() { }
		virtual void onEnable() { }
		virtual void onDisable() { }
	protected:
		Entity* ent_;
		EntityManager* mngr_;
		bool enable_ = true;
	};
}