#include <EC/component.h>

namespace magma_engine
{
	namespace ec {
		Component::Component() : ent() {}
		Component::Component(Entity* entity) : ent(entity) {}
		Component::~Component() {}

		void Component::setContext(Entity* ent_)
		{
			ent = ent_;
		}

		bool Component::isEnable()
		{
			return enable;
		}

		void Component::setEnable(bool set_)
		{
			enable = set_;
			if (set_)
				onEnable();
			else
				onDisable();
		}
		bool Component::initComponent(std::map<std::string, std::string> args)
		{
			return false;
		}
		bool Component::start()
		{
			return false;
		}
		void Component::update(float deltaTime)
		{
		}
		void Component::render()
		{
		}
		void Component::onEnable()
		{
		}
		void Component::onDisable()
		{
		}
		void Component::recieve(const Message&)
		{
		}
	}
}
