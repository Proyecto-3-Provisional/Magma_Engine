#pragma once

#include <EC/component.h>
#include <EC/vector3D.h>
#include <Physics/rigidbody.h>
#include <EC/transform.h>

namespace magma_game
{
	class EnemyController : public magma_engine::Component
	{
	public:
		EnemyController();
		~EnemyController();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();

		void update(float deltaTime);

		void roamBehavior();

	private:
		magma_engine::Rigidbody* rb = nullptr;
		magma_engine::Transform* tr = nullptr;

		float enemySpeed;

		float timeBetweenMovements;
		float currTimeBetweenMovements;
	};
}