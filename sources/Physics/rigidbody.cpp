#include "rigidbody.h"
#include "physics_manager.h"
#include "../EC/entity.h"
#include "../EC/transform.h"

Rigidbody::Rigidbody() : scale(Vector3D(0, 0, 0))
{
}

Rigidbody::Rigidbody(const Vector3D& scale_) : scale(scale_)
{
}

Rigidbody::~Rigidbody()
{
	PhysicsManager::instance()->deleteRigidBody(rigidPtr->getUserIndex());
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

bool Rigidbody::isOnCollision()
{
	return (PhysicsManager::instance()->getArrayOfIndexColliders(rigidPtr->getUserIndex()).size() > 0);
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