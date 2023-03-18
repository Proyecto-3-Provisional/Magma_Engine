#include "rigidbody.h"
#include "../Physics/physics_manager.h"

Rigidbody::Rigidbody(Vector3D scale_, Vector3D pos_) : scale(scale_), pos(pos_), index(0)
{
}

bool Rigidbody::initComponent()
{
	if (PhysicsManager::getInstance() != nullptr)
		index = PhysicsManager::getInstance()->addRigidBody(
			scale.getX(), scale.getY(), scale.getZ(), pos.getX(), pos.getY(), pos.getZ());
	return true;
}