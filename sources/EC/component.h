// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <EC/ec.h>
#include <EC/messages.h>
#include <map>
#include <string>

namespace magma_engine
{
	namespace ec
	{
		struct Component
		{
		public:
			Component();
			Component(Entity* entity);
			virtual ~Component() {}
			void setContext(Entity* ent_, EntityManager* mngr_);
			bool isEnable();
			void setEnable(bool set_);

			virtual bool initComponent(std::map<std::string, std::string> args);
			virtual bool start() { return false; };
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

