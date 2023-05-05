#pragma once

#include <EC/entity.h>

namespace magma_engine {
	class Rigidbody;
}

namespace magma_game
{
	class PowerUpComponent : public magma_engine::Component
	{
	public:
		enum class PowerupType
		{
			IncreaseSize,
			DecreaseSize,
			IncreaseSpeed,
			DecreaseSpeed
		};

		PowerUpComponent();
		~PowerUpComponent() {};

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		void onCollision(magma_engine::Entity* ent);
		void update(float deltaTime);

	private:
		magma_engine::Rigidbody* rb = nullptr;

		float size;
		float vel;
	};
}
