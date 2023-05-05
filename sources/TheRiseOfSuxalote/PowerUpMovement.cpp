//#include "PowerUpMovement.h"
//
//#include <math.h>
//
//#include <EC/entity.h>
//#include <Physics/rigidbody.h>
//
//magma_game::PowerUpMovement::PowerUpMovement(int x, int z) : x(x), z(z)
//{
//}
//
//magma_game::PowerUpMovement::~PowerUpMovement()
//{
//}
//
//bool magma_game::PowerUpMovement::initComponent()
//{
//	try {
//		startMove();
//		return true;
//	}
//	catch (...) {
//		return false;
//	}
//}
//
//void magma_game::PowerUpMovement::startMove()
//{
//	float scale = sqrt(x * x + z * z);
//	x = x / scale;
//	z = z / scale;
//	ent->getComponent<magma_engine::Rigidbody>()->addForce(magma_engine::Vector3D(x * velScale, 0, z * velScale));
//}
