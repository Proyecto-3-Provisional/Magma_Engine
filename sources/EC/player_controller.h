#pragma once

//#include <EC/entity.h>
#include <Physics/rigidbody.h>



namespace magma_engine
{
	class Rigidbody;

	class PlayerControllah : public ec::Component
	{
	public:
		PlayerControllah();
		~PlayerControllah();

		bool initComponent();
		void update(float deltaTime);


	private:
		Rigidbody* rb = nullptr;
	};
}