#include <EC/component.h>

namespace magma_engine
{
	ec::Component::Component() : ent(), mngr() {}
	ec::Component::Component(Entity* entity) : ent(entity), mngr() {}
	ec::Component::~Component() {}

	void ec::Component::setContext(Entity* ent_, EntityManager* mngr_)
	{
		ent = ent_;
		mngr = mngr_;
	}

	bool ec::Component::isEnable()
	{
		return enable;
	}

	void ec::Component::setEnable(bool set_)
	{
		enable = set_;
		if (set_)
			onEnable();
		else
			onDisable();
	}
	bool ec::Component::initComponent(std::map<std::string, std::string> args)
	{
		return false;
	}
	bool ec::Component::start()
	{
		return false;
	}
	void ec::Component::update(float deltaTime)
	{
	}
	void ec::Component::render()
	{
	}
	void ec::Component::onEnable()
	{
	}
	void ec::Component::onDisable()
	{
	}
	void ec::Component::recieve(const Message&)
	{
	}
}
