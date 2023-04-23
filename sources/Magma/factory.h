#pragma once

#include <EC/component.h>

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


