#include <Physics/rigidbody.h>
#include <Physics/physics_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>
#include <Render/mesh.h>

namespace magma_engine
{
	Rigidbody::Rigidbody() : proportions({1, 1, 1}), linearDamping(0.5f), angularDamping(0)
	{
	}

	Rigidbody::~Rigidbody()
	{
		PhysicsManager::instance()->deleteRigidBody(rigidPtr->getUserIndex());
	}

	bool Rigidbody::initComponent(std::map<std::string, std::string> args)
	{
		return true;
	}

	bool Rigidbody::start()
	{
		trPtr = ent->getComponent<Transform>();
		meshPtr = ent->getComponent<Mesh>();

		if (trPtr == nullptr)
			return false;
		try {
			if (meshPtr->getObj() == nullptr) /* meshPtr == nullptr */
				return false;
		}
		catch (...) {
			return false;
		}	

		Vector3D pos = trPtr->getPos();
		proportions = meshPtr->getProportions();

		if (PhysicsManager::instance() != nullptr) {
			int index = PhysicsManager::instance()->addRigidBody(
				proportions.getX() / 2,
				proportions.getY() / 2,
				proportions.getZ() / 2,
				pos.getX(),
				pos.getY(),
				pos.getZ());

			rigidPtr = PhysicsManager::instance()->getRigidBody(index);

			rigidPtr->setDamping(linearDamping, angularDamping);
		}
		else {
			return false;
		}

		return true;
	}

	void Rigidbody::update(float deltaTime)
	{
		if (trPtr != nullptr)
		{
			// Actualizamos la posición del transform
			trPtr->setPosition(PhysicsManager::instance()->getPos(rigidPtr->getUserIndex()));

			// Actualizamos la rotación del collider 
			Quaternion q = meshPtr->getOrientation();
			rigidPtr->getWorldTransform().setRotation(btQuaternion(q.getX(), q.getY(), q.getZ(), q.getW()));

			// Actualizamos la escala del collider en función del transform
			rigidPtr->getCollisionShape()->setLocalScaling(btVector3(trPtr->getScale().getX(), trPtr->getScale().getY(), trPtr->getScale().getZ()));
		}
	}

	bool Rigidbody::isCollideWith(int indexCollide)
	{
		return PhysicsManager::instance()->isCollide(rigidPtr->getUserIndex(), indexCollide);
	}

	bool Rigidbody::isOnCollision()
	{
		return (PhysicsManager::instance()->getArrayOfColliders(rigidPtr->getUserIndex()).size() > 0);
	}

	std::vector<ec::Entity*> Rigidbody::getCollisionObjs()
	{
		return PhysicsManager::instance()->getArrayOfColliders(rigidPtr->getUserIndex());
	}

	void Rigidbody::addForce(const Vector3D& force)
	{
		PhysicsManager::instance()->addForceTo(rigidPtr->getUserIndex(), force);
	}

	int Rigidbody::getIndex()
	{
		return rigidPtr->getUserIndex();
	}

	void Rigidbody::setLinearDamping(float d) {
		linearDamping = d;
		rigidPtr->setDamping(linearDamping, angularDamping);
	}

	void Rigidbody::setAngularDamping(float d) {
		angularDamping = d;
		rigidPtr->setDamping(linearDamping, angularDamping);
	}
	Vector3D Rigidbody::getVelocity()
	{
		return Vector3D(rigidPtr->getLinearVelocity().getX(), rigidPtr->getLinearVelocity().getY(), rigidPtr->getLinearVelocity().getZ());
	}
}

