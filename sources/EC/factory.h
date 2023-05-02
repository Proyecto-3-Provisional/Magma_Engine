#pragma once

#include <EC/component.h>

namespace magma_engine
{
	class Factory
	{
	public:
		Factory() {};
		virtual ~Factory() {};
		virtual Component* createComponent(Entity* ent = nullptr) = 0;
	};
}


