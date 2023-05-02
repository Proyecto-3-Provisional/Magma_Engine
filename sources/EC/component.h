// Samir Genaim (modificado mas o menos en funcion de nuestras necesidades)

#pragma once

#include <EC/messages.h>
#include <map>
#include <string>

namespace magma_engine
{
	class Entity;

	class Component
	{
	public:
		Component();
		Component(Entity* entity);
		virtual ~Component();
		void setContext(Entity* ent_);
		bool isEnable();
		void setEnable(bool set_);

		// ¡Si el componente falla, hay que borrar lo que haya ya creado!
		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		virtual void update(float deltaTime);
		virtual void render();
		virtual void onEnable();
		virtual void onDisable();

		virtual void recieve(const Message&);

	protected:

		Entity* ent;
		bool enable = true;
	};
}

