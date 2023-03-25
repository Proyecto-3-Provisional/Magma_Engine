#include "rigidbody.h"
#include "physics_manager.h"
#include "../ECS/entity.h"
#include "../ECS/transform.h"

Rigidbody::Rigidbody(const Vector3D& scale_) : scale(scale_)
{
}

bool Rigidbody::initComponent()
{
	trPtr = ent->getComponent<Transform>();

	if (trPtr == nullptr)
		return false;

	Vector3D pos = trPtr->getPos();

	if (PhysicsManager::instance() != nullptr) {
		int index = PhysicsManager::instance()->addRigidBody(
			scale.getX(), scale.getY(), scale.getZ(), pos.getX(), pos.getY(), pos.getZ());

		rigidPtr = PhysicsManager::instance()->getRigidBody(index);

		if (rigidPtr == nullptr)
			return false;
	}

	return true;
}

void Rigidbody::update(float deltaTime)
{
	Vector3D pos = PhysicsManager::instance()->getTransform(rigidPtr->getUserIndex());
	trPtr->setPosition(pos);
}

bool Rigidbody::isCollideWith(int indexCollide)
{
	return PhysicsManager::instance()->isCollide(rigidPtr->getUserIndex(), indexCollide);
}

bool Rigidbody::isOnCollision(std::vector<int>& indexCollides)
{
	indexCollides = PhysicsManager::instance()->getArrayOfIndexColliders(rigidPtr->getUserIndex());
	return (indexCollides.size() > 0);
}

void Rigidbody::addForce(const Vector3D& force)
{
	PhysicsManager::instance()->addForceTo(rigidPtr->getUserIndex(),
		btVector3(force.getX(), force.getY(), force.getZ()));
}

int Rigidbody::getIndex()
{
	return rigidPtr->getUserIndex();
}