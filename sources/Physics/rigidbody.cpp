#include <Physics/rigidbody.h>
#include <Physics/physics_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>

namespace magma_engine
{
	Rigidbody::Rigidbody() : scale()
	{
	}

	Rigidbody::~Rigidbody()
	{
		PhysicsManager::instance()->deleteRigidBody(rigidPtr->getUserIndex());
	}

	bool Rigidbody::initComponent(const Vector3D& scale_)
	{
		scale = scale_;
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

		Vector3D pos = PhysicsManager::instance()->getPos(rigidPtr->getUserIndex());
		
		if (trPtr != nullptr)
		{
			trPtr->setPosition(pos);

			btCollisionShape* shape = rigidPtr->getCollisionShape();
			shape->setLocalScaling(btVector3(trPtr->getScale().getX(), trPtr->getScale().getY(), trPtr->getScale().getZ()));
		}
	}

	bool Rigidbody::isCollideWith(int indexCollide)
	{
		return PhysicsManager::instance()->isCollide(rigidPtr->getUserIndex(), indexCollide);
	}

	bool Rigidbody::isOnCollision()
	{
		return (PhysicsManager::instance()->getArrayOfIndexColliders(rigidPtr->getUserIndex()).size() > 0);
	}

	std::vector<int> Rigidbody::getCollisionObjs()
	{
		return PhysicsManager::instance()->getArrayOfIndexColliders(rigidPtr->getUserIndex());
	}

	void Rigidbody::addForce(const Vector3D& force)
	{
		PhysicsManager::instance()->addForceTo(rigidPtr->getUserIndex(), force);
	}

	int Rigidbody::getIndex()
	{
		return rigidPtr->getUserIndex();
	}
}

