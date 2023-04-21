#pragma once

#include <EC/component.h>
#include <string>
#include <map>

namespace magma_engine
{
	class Factory
	{
	public:
		Factory() {};
		virtual ~Factory() {};
		virtual ec::Component* createComponent(ec::Entity* ent = nullptr) = 0;
	};
}


