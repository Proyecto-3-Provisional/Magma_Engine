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

	ec::Component* findAndCreate(const std::string& name, ec::Entity* ent = nullptr);
	void addFactory(const std::string& name, Factory* fact);
private:
	std::map<std::string, Factory*> map_;
	std::list<Factory*> list_;
	template <typename T>
	ec::Component* createComponent() { return new T; };
};
