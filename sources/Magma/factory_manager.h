#pragma once
#include <string>
#include <map>
#include "../EC/component.h"

class Factory;

class FactoryManager
{
public:
	~FactoryManager();

	ec::Component* findAndCreate(const std::string& name, std::map<std::string, std::string> args, ec::Entity* e = nullptr);
	void addFactory(const std::string& name, Factory* f);
private:
	std::map<std::string, Factory*> map_;
	template <typename T>
	ec::Component* createComponent() { return new T; };
};
