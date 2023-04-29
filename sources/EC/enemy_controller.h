#pragma once

#include <Physics/rigidbody.h>

namespace magma_engine
{
	class Rigidbody;

	class EnemyController : public ec::Component
	{
	public:
		EnemyController();
		~EnemyController();

		bool initComponent(Transform* playerTransform_, float playerSpeed_ = 10000.0f, float timeBetweenMovements_ = 2.0f, bool chasing_ = true);
		void update(float deltaTime);


	private:
		Rigidbody* rb = nullptr;
		Transform* tr = nullptr;
		Transform* playerTransform = nullptr;
		float enemySpeed;

		Vector3D movementDirection;

		//true para perseguir al jugador,false para huir
		bool chasing;

		float timeBetweenMovements;
		float currTimeBetweenMovements;
	};
}