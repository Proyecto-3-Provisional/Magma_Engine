#pragma once
#include <EC/component.h>

namespace magma_engine
{
	class Rigidbody;
	
	class Size_Temp : public Component
	{
	public:
		Size_Temp();
		virtual ~Size_Temp();

		virtual bool initComponent();
		void update(float deltaTime);

		float tam = 1.0f;
	};
}