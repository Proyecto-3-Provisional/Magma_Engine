#pragma once

#include <Physics/rigidbody.h>

namespace magma_engine
{
	class Rigidbody;

	class PlayerController : public ec::Component
	{
	public:
		PlayerController();
		~PlayerController();

		bool initComponent(float playerSpeed_ = 10000.0f, float timeBetweenMovements_ = 1.0f);
		void update(float deltaTime);


	private:
		Rigidbody* rb = nullptr;
		Transform* tr = nullptr;
		float playerSpeed;

		Vector3D movementDirection;
		//simula al ajolote nadando a "empujones"
		float timeBetweenMovements;
		float currTimeBetweenMovements;
	};
}