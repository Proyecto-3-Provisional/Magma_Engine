#pragma once

#include "../EC/component.h"
#include <string>
#include <map>

class Factory
{
public:
	Factory();
	virtual ~Factory();
	virtual ec::Component* createComponent(std::map<std::string, std::string> args, ec::Entity* ent = nullptr) = 0;
};
