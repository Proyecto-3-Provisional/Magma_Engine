#include <TheRiseOfSuxalote/enemy_controller.h>

#include <Input/input_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>

namespace magma_game
{
	EnemyController::EnemyController() : enemySpeed(0.0f), timeBetweenMovements(0.0f), currTimeBetweenMovements(0.0f)
	{
	}

	EnemyController::~EnemyController()
	{

	}

	bool EnemyController::initComponent(std::map<std::string, std::string> args)
	{
		try {
			enemySpeed = stof(args["enemySpeed"]);
			timeBetweenMovements = stof(args["timeBetweenMovements"]);
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente enemy_controller:\n\n     " << e.what() << "\n\n";

			return false;
		}
		return true;
	}

	bool EnemyController::start()
	{
		currTimeBetweenMovements = timeBetweenMovements;
		rb = ent->getComponent<magma_engine::Rigidbody>();
		tr = ent->getComponent<magma_engine::Transform>();
		return (tr != nullptr && rb != nullptr);
	}

	void EnemyController::update(float deltaTime)
	{
		bool move = false;

		if (currTimeBetweenMovements <= 0) {
			roamBehavior();
			currTimeBetweenMovements = timeBetweenMovements;
		}

		currTimeBetweenMovements -= deltaTime;
	}

	void EnemyController::roamBehavior()
	{
		int r = rand() % 4;
		
		switch (r)
		{
		case 0:
			rb->addForce(magma_engine::Vector3D{1,0,0} * enemySpeed);
			break;

		case 1:
			rb->addForce(magma_engine::Vector3D{ -1,0,0 } *enemySpeed);
			break;

		case 2:
			rb->addForce(magma_engine::Vector3D{ 0,0,1 } *enemySpeed);
			break;

		case 3:
			rb->addForce(magma_engine::Vector3D{ 0,0,-1 } *enemySpeed);
			break;

		default:
			break;
		}
	}
}