#include <EC/factory_manager.h>
#include <EC/factory.h>

namespace magma_engine
{
	FactoryManager::~FactoryManager()
	{
		for (std::pair<std::string, Factory*> i : map_)
			delete i.second;
		map_.clear();
	}

	Component* FactoryManager::findAndCreate(const std::string& name, Entity* e)
	{
		std::map<std::string, Factory*>::iterator it = map_.find(name);
		if (it == map_.end())
			return nullptr;
		return (*it).second->createComponent(e);
	}

	void FactoryManager::addFactory(const std::string& name, Factory* f)
	{
		map_[name] = f;
	}
}

