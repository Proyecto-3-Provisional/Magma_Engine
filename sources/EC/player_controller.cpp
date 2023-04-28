#include "player_controller.h"

#include <Input/input_manager.h>
#include <EC/entity.h>


namespace magma_engine
{
	PlayerController::PlayerController()
	{
	}

	PlayerController::~PlayerController()
	{

	}

	bool PlayerController::initComponent()
	{
		try {
			rb = ent->getComponent<Rigidbody>();
			 int i = 0;
			//inputMgr = Singleton<magma_engine::InputManager>::instance();
			return true;
		}
		catch (...) {
			return false;
		}
		return false;
	}

	void PlayerController::update(float deltaTime)
	{
		if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_A)) {
			rb->addForce(Vector3D(-1, 0, 0));
		}
		else if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_D)) {
			rb->addForce(Vector3D(1, 0, 0));
		}
		else if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_W)) {
			rb->addForce(Vector3D(0, 0, -1));
		}
		else if (Singleton<InputManager>::instance()->isKeyDown(SCANCODE_S)) {
			rb->addForce(Vector3D(0, 0, 1));
		}
	}
}