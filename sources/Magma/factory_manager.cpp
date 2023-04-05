#include "factory_manager.h"
#include "factory.h"

FactoryManager::~FactoryManager()
{
	for (std::pair<std::string, Factory*> i : map_)
		delete i.second;
	map_.clear();
}

ec::Component* FactoryManager::findAndCreate(ec::Entity* e)
{
	return list_.front()->createComponent(e);
	//std::map<std::string, Factory*>::iterator it = map_.find(name);
	//if (it != map_.end())
		//return (*it).second->createComponent(args, e);

	//throw "ERROR: NO SE HA PODIDO LEER EL COMPONENTE: " + name + "\n";
}

void FactoryManager::addFactory(Factory* f)
{
	list_.push_back(f);
	//map_[name] = f;
}