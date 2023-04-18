// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include "ec.h"
#include "messages.h"

namespace ec {
	struct Component {
	public:
		Component() : ent(), mngr() {}
		Component(Entity* entity) : ent(), mngr() { ent = entity; }
		virtual ~Component() { }
		void setContext(Entity* ent_, EntityManager* mngr_);
		inline bool isEnable() { return enable; }
		void setEnable(bool set_);
		
		virtual bool initComponent() { return false; };
		virtual void update(float deltaTime) {};
		virtual void render() {};
		virtual void onEnable() {};
		virtual void onDisable() {};

		// a method to receive a message, will be called by the sender or
		// from the manager when a message is sent to all
		//
		// the struct msg is forward declared in ecs.h, the actual meesage will
		// be defined by the user
		//
		virtual void recieve(const Message&) {};
	protected:
		Entity* ent;
		EntityManager* mngr;
		bool enable = true;
	};
}