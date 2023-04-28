#pragma once

//#include <EC/entity.h>
#include <Physics/rigidbody.h>



namespace magma_engine
{
	class Rigidbody;

	class PlayerController : public ec::Component
	{
	public:
		PlayerController();
		~PlayerController();

		bool initComponent();
		void update(float deltaTime);


	private:
		Rigidbody* rb = nullptr;
	};
}