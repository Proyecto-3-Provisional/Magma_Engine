#include "rigidbody.h"
#include "physics_manager.h"
#include "../ECS/entity.h"
#include "../ECS/transform.h"

Rigidbody::Rigidbody(Vector3D scale_) : scale(scale_), index(0)
{
}

bool Rigidbody::initComponent()
{
	trPtr = ent->getComponent<Transform>();
	if (trPtr == nullptr)
		return false;
	Vector3D pos = trPtr->getPos();
	if (PhysicsManager::getInstance() != nullptr)
		index = PhysicsManager::getInstance()->addRigidBody(
			scale.getX(), scale.getY(), scale.getZ(), pos.getX(), pos.getY(), pos.getZ());
	return true;
}

void Rigidbody::update(float deltaTime)
{
	Vector3D pos = PhysicsManager::getInstance()->getTransform(index);
	trPtr->setPosition(pos);
}

int Rigidbody::getIndex()
{
	return index;
}

void Rigidbody::setIndex(int index_)
{
	index = index_;
}
