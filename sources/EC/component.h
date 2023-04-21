// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <EC/ec.h>
#include <EC/messages.h>

namespace magma_engine
{
	namespace ec
	{
		struct Component
		{
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

			virtual void recieve(const Message&) {};

		protected:

			Entity* ent;
			EntityManager* mngr;
			bool enable = true;
		};
	}
}

