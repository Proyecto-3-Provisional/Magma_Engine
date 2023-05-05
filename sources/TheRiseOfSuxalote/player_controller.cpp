#include <Input/input_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>

#include <TheRiseOfSuxalote/player_controller.h>

namespace magma_game
{
	PlayerController::PlayerController() : speed(0.0f), timeBetweenMovements(0.0f), currTimeBetweenMovements(0.0f)
	{
	}

	PlayerController::~PlayerController()
	{

	}

	bool PlayerController::initComponent(std::map<std::string, std::string> args)
	{
		try {
			speed = stof(args["playerSpeed"]);
			timeBetweenMovements = stof(args["timeBetweenMovements"]);
			currTimeBetweenMovements = stof(args["timeBetweenMovements"]); ;

			magma_engine::Vector3D movementDirection(0, 0, 0);
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente player_controller:\n\n     " << e.what() << "\n\n";
			return false;
		}
		return true;
	}

	bool PlayerController::start()
	{
		tr = ent->getComponent<magma_engine::Transform>();
		rb = ent->getComponent<magma_engine::Rigidbody>();
		return (tr != nullptr && rb != nullptr);
	}

	void PlayerController::update(float deltaTime)
	{
		bool move = false;

		if (currTimeBetweenMovements < 0.0f) {
			movementDirection = { 0,0,0 };

			if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(SCANCODE_A)) {

				rb->addForce(magma_engine::Vector3D(-1, 0, 0) * speed);
				movementDirection += magma_engine::Vector3D(-1, 0, 0);
				move = true;
			}
		
			if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(SCANCODE_D)) {

				rb->addForce(magma_engine::Vector3D(1, 0, 0) * speed);
				movementDirection += magma_engine::Vector3D(1, 0, 0);

				move = true;

			}

			if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(SCANCODE_W)) {

				rb->addForce(magma_engine::Vector3D(0, 0, -1) * speed);
				movementDirection += magma_engine::Vector3D(0, 0, -1);

				move = true;

			}

			if (Singleton<magma_engine::InputManager>::instance()->isKeyDown(SCANCODE_S)) {

				rb->addForce(magma_engine::Vector3D(0, 0, 1) * speed);
				movementDirection += magma_engine::Vector3D(0, 0, 1);

				move = true;

			}

			if (move && movementDirection.magnitude() != 0) {
				tr->setDirection(movementDirection);
				currTimeBetweenMovements = timeBetweenMovements;
			}

		}

		currTimeBetweenMovements -= deltaTime;

	}

	void PlayerController::setVelocity(float velocity)
	{
		speed = speed + velocity;
	}
}