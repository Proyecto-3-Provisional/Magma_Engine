#include <Magma/factory_manager.h>
#include <Magma/factory.h>


namespace magma_engine
{
	FactoryManager::~FactoryManager()
	{
		for (std::pair<std::string, Factory*> i : map_)
			delete i.second;
		map_.clear();
	}

	ec::Component* FactoryManager::findAndCreate(const std::string& name, ec::Entity* e)
	{
		std::map<std::string, Factory*>::iterator it = map_.find(name);
		if (it != map_.end())
			return (*it).second->createComponent(e);

		throw "ERROR: NO SE HA PODIDO LEER EL COMPONENTE: " + name + "\n";
	}

	void FactoryManager::addFactory(const std::string& name, Factory* f)
	{
		map_[name] = f;
	}
}

