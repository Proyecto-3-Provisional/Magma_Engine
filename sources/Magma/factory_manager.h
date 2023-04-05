#pragma once
#include <string>
#include <map>
#include <list>
#include "../EC/component.h"
#include "../singleton.h"

class Factory;

class FactoryManager : public Singleton<FactoryManager>
{
public:
	~FactoryManager();

	ec::Component* findAndCreate(ec::Entity* e = nullptr);
	void addFactory(Factory* f);
private:
	std::map<std::string, Factory*> map_;
	std::list<Factory*> list_;
	template <typename T>
	ec::Component* createComponent() { return new T; };
};
