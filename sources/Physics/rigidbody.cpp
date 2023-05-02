#include <Physics/rigidbody.h>
#include <Physics/physics_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>
#include <Render/mesh.h>

namespace magma_engine
{
	Rigidbody::Rigidbody() : proportions({1, 1, 1}), linearDamping(0.5f), angularDamping(0), meshPtr(nullptr)
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
		try {

			trPtr = ent->getComponent<Transform>();
			meshPtr = ent->getComponent<Mesh>();


			Vector3D pos = trPtr->getPos();
			proportions = meshPtr->getProportions();

		if (PhysicsManager::instance() != nullptr) {


			int index = PhysicsManager::instance()->addRigidBody(
				ent,
				proportions.getX() / 2,
				proportions.getY() / 2,
				proportions.getZ() / 2,
				pos.getX(),
				pos.getY(),
				pos.getZ()
			);

				rigidPtr = PhysicsManager::instance()->getRigidBody(index);

				rigidPtr->setDamping(linearDamping, angularDamping);
			}
			else
				std::cout << "WARNING! - physicsManager no creado\n\n";
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente rigidbody:\n\n     " << e.what() << "\n\n";
			return false;
		}

		return true;
	}

	void Rigidbody::update(float deltaTime)
	{
		if (trPtr != nullptr)
		{
			// Actualizamos la posici�n del transform
			trPtr->setPosition(PhysicsManager::instance()->getPos(rigidPtr->getUserIndex()));

			// Actualizamos la rotaci�n del collider 
			Quaternion q = meshPtr->getOrientation();
			rigidPtr->getWorldTransform().setRotation(btQuaternion(q.getX(), q.getY(), q.getZ(), q.getW()));

			// Actualizamos la escala del collider en funci�n del transform
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

	std::vector<Entity*> Rigidbody::getCollisionObjs()
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

