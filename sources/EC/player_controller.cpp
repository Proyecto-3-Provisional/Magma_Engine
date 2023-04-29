#include "player_controller.h"

#include <Input/input_manager.h>
#include <EC/entity.h>
#include <EC/transform.h>


namespace magma_engine
{
	PlayerController::PlayerController() : playerSpeed(0.0f), timeBetweenMovements(0.0f), currTimeBetweenMovements(0.0f)
	{
	}

	PlayerController::~PlayerController()
	{

	}

	bool PlayerController::initComponent(float playerSpeed_, float timeBetweenMovements_)
	{
		try {
			rb = ent->getComponent<Rigidbody>();
			tr = ent->getComponent<Transform>();

			playerSpeed = playerSpeed_;
			timeBetweenMovements = timeBetweenMovements_;
			currTimeBetweenMovements = timeBetweenMovements;
			
			Vector3D movementDirection(0, 0, 0);
		}
		catch (...) {
			return false;
		}
		return false;
	}

	void PlayerController::update(float deltaTime)
	{
		bool move = false;

		if (currTimeBetweenMovements < 0.0f) {
			movementDirection = { 0,0,0 };

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_A)) {

				rb->addForce(Vector3D(-1, 0, 0) * playerSpeed * deltaTime);
				movementDirection += Vector3D(-1, 0, 0);
				move = true;
			}
		
			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_D)) {

				rb->addForce(Vector3D(1, 0, 0) * playerSpeed * deltaTime);
				movementDirection += Vector3D(1, 0, 0);

				move = true;

			}

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_W)) {

				rb->addForce(Vector3D(0, 0, -1) * playerSpeed * deltaTime);
				movementDirection += Vector3D(0, 0, -1);

				move = true;

			}

			if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_S)) {

				rb->addForce(Vector3D(0, 0, 1) * playerSpeed * deltaTime);
				movementDirection += Vector3D(0, 0, 1);

				move = true;

			}

			if (move) {
				tr->setDirection(movementDirection);
				currTimeBetweenMovements = timeBetweenMovements;
			}

		}

		currTimeBetweenMovements -= deltaTime;

	}
}