// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <string>
#include "ecs.h"

namespace ec {
	struct Component {
	public:
		Component() : ent(), mngr() {}
		virtual ~Component() { }
		void setContext(Entity* ent_, EntityManager* mngr_);
		inline bool isEnable() { return enable; }
		void setEnable(bool set_);
		
		virtual void initComponent() { }
		virtual void update() { }
		virtual void render() { }
		virtual void onEnable() { }
		virtual void onDisable() { }
	protected:
		Entity* ent;
		EntityManager* mngr;
		bool enable = true;
	};
}