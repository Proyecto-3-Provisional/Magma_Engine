#include <TheRiseOfSuxalote/power_up.h>

#include <Physics/rigidbody.h>
#include <TheRiseOfSuxalote/size_temp.h>
#include <TheRiseOfSuxalote/player_controller.h>

magma_game::PowerUpComponent::PowerUpComponent() : size(0.0f), vel(0.0f)
{
}

bool magma_game::PowerUpComponent::initComponent(std::map<std::string, std::string> args)
{
	try {
		size = stof(args["Size"]);
		vel = stof(args["Vel"]);
	}
	catch (std::exception& e) {
		std::cout << "WARNING! - error en un componente power_up:\n\n     " << e.what() << "\n\n";

		return false;
	}
	return true;
}

bool magma_game::PowerUpComponent::start()
{
	srand(time(NULL));

	rb = ent->getComponent<magma_engine::Rigidbody>();
	return (rb != nullptr);
}

void magma_game::PowerUpComponent::update(float deltaTime)
{
	if (rb->isOnCollision())
	{
		auto ents = rb->getCollisionObjs();
		for (auto e : ents)
		{
			if (e->hasComponent<PlayerController>())
				onCollision(e);
		}
	}
}

void magma_game::PowerUpComponent::onCollision(magma_engine::Entity* e)
{
	PowerupType powerupType = static_cast<PowerupType>(rand() % 4);

	switch (powerupType) {
	case PowerupType::IncreaseSize:
		e->getComponent<Size_Temp>()->setTam(size);
		break;
	case PowerupType::DecreaseSize:
		e->getComponent<Size_Temp>()->setTam(-size);
		break;
	case PowerupType::IncreaseSpeed:
		e->getComponent<PlayerController>()->setVelocity(vel);
		break;
	case PowerupType::DecreaseSpeed:
		e->getComponent<PlayerController>()->setVelocity(-vel);
		break;
	}

	ent->setAlive(false);
}