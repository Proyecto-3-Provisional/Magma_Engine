#include <Physics/physics_manager.h>
#include <btBulletDynamicsCommon.h>
#include <EC/vector3D.h>

#include <iostream>
#include <stdio.h>
#include <algorithm>

namespace magma_engine
{
	PhysicsManager::PhysicsManager() : collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr) {}

	PhysicsManager::~PhysicsManager() {}

	int PhysicsManager::initPhysics()
	{
		collisionConfiguration = new btDefaultCollisionConfiguration();

		dispatcher = new btCollisionDispatcher(collisionConfiguration);

		overlappingPairCache = new btDbvtBroadphase();

		solver = new btSequentialImpulseConstraintSolver;

		dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

		dynamicsWorld->setGravity(btVector3(0, 0, 0));

		collisionShapes = new btAlignedObjectArray<btCollisionShape*>();

		return 1;
	}

	int PhysicsManager::addRigidBody(Entity* e, const double& xShape, const double& yShape, const double& zShape, 
		const double& xTransform, const double& yTransform, const double& zTransform)
	{
		btCollisionShape* rigidBodyShape = new btBoxShape(btVector3(btScalar(xShape), btScalar(yShape), btScalar(zShape)));

		collisionShapes->push_back(rigidBodyShape);

		btTransform newRigidBody;
		newRigidBody.setIdentity();
		newRigidBody.setOrigin(btVector3(btScalar(xTransform), btScalar(yTransform), btScalar(zTransform)));

		btScalar mass(1.);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);

		if (isDynamic)
			rigidBodyShape->calculateLocalInertia(mass, localInertia);

		btDefaultMotionState* myMotionState = new btDefaultMotionState(newRigidBody);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, rigidBodyShape, localInertia);

		btRigidBody* body = new btRigidBody(rbInfo);
		body->setActivationState(DISABLE_DEACTIVATION);

		body->setUserIndex(dynamicsWorld->getNumCollisionObjects());

		dynamicsWorld->addRigidBody(body);
		entities.push_back(e);

		return body->getUserIndex();
	}

	void PhysicsManager::deleteRigidBody(const int& userIndex)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[userIndex];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;

		int size = dynamicsWorld->getCollisionObjectArray().size();

		// Como el array de colisiones rellena el hueco con el último elemento...
		if (size > 0 && size != userIndex) { // Si el que hemos eliminado no era el último...
			btCollisionObject* obj1 = dynamicsWorld->getCollisionObjectArray()[userIndex];
			btRigidBody* body1 = btRigidBody::upcast(obj1);
			body1->setUserIndex(userIndex); // Actualizamos su índice (para que se corresponda con su nueva pos en el array)
			
			entities[userIndex] = entities.back(); // Actualizamos el vector de entidades
		}
		
		// Eliminamos la última entidad del vector. Bien porque el rigidbody era el último del array o porque
		// no lo era y copiamos el último al hueco dejado por el eliminado
		entities.pop_back();
	}

	void PhysicsManager::deleteRigidBodies(std::vector<int>& vIndex)
	{
		std::sort(vIndex.begin(), vIndex.end(), std::greater<int>());
		for (int i : vIndex)
			deleteRigidBody(i);
	}

	void PhysicsManager::update(float deltaTime)
	{
		dynamicsWorld->stepSimulation(deltaTime, 10);

		for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if (body && body->getMotionState())
			{
				body->getMotionState()->getWorldTransform(trans);
			}
		}
	}

	void PhysicsManager::updateCollisions()
	{
		btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

		for (int i = 0; i < collisionPairs.size(); ++i) {
			btBroadphasePair& collisionPair = collisionPairs[i];

			btRigidBody* body1 = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
			btRigidBody* body2 = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

			if (body1 && body2 && body1->getInvMass() > 0.0f && body2->getInvMass() > 0.0f) {

				if (body1->getUserIndex() == -1 || body2->getUserIndex() == -1) {
					std::cout << "Al menos uno de los objetos no tiene índice de usuario asignado" << std::endl;
					continue;
				}

				if (body1->getUserIndex() == body2->getUserIndex()) {
					std::cout << "Los objetos son iguales" << std::endl;
					continue;
				}

				std::cout << "Colisión detectada entre objetos " << body1->getUserIndex() << " y " << body2->getUserIndex() << std::endl;
			}
		}
	}

	bool PhysicsManager::isCollide(const int& index1, const int& index2)
	{
		btCollisionObject* obj1 = dynamicsWorld->getCollisionObjectArray()[index1];
		btRigidBody* body1 = btRigidBody::upcast(obj1);
		btCollisionObject* obj2 = dynamicsWorld->getCollisionObjectArray()[index2];
		btRigidBody* body2 = btRigidBody::upcast(obj2);

		btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

		bool colision = false;
		for (int i = 0; i < collisionPairs.size(); ++i) {
			btBroadphasePair& collisionPair = collisionPairs[i];

			btRigidBody* body1Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
			btRigidBody* body2Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

			if (body1Pair && body2Pair && body1Pair->getInvMass() > 0.0f && body2Pair->getInvMass() > 0.0f) {

				if ((body1 == body1Pair && body2 == body2Pair) || (body2 == body1Pair && body1 == body2Pair)) {
					colision = true;
					break;
				}
			}
		}

		return colision;
	}

	std::vector<Entity*> PhysicsManager::getArrayOfColliders(int index)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[index];
		btRigidBody* body = btRigidBody::upcast(obj);

		btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

		std::vector<Entity*> colliders;
		for (int i = 0; i < collisionPairs.size(); ++i) {
			btBroadphasePair& collisionPair = collisionPairs[i];

			btRigidBody* body1Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
			btRigidBody* body2Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

			if (body1Pair && body2Pair && body1Pair->getInvMass() > 0.0f && body2Pair->getInvMass() > 0.0f) {

				if (body == body1Pair) colliders.push_back(entities[body2Pair->getUserIndex()]);
				else if (body == body2Pair) colliders.push_back(entities[body1Pair->getUserIndex()]);
			}
		}

		return colliders;
	}

	Vector3D PhysicsManager::getPos(int index)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[index];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}

		return Vector3D(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}

	btRigidBody* PhysicsManager::getRigidBody(int index)
	{
		if (dynamicsWorld->getCollisionObjectArray().size() > index) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[index];
			return btRigidBody::upcast(obj);
		}
		else
			return nullptr;
	}

	void PhysicsManager::addForceTo(int index, const Vector3D& force)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[index];
		btRigidBody::upcast(obj)->applyCentralImpulse(btVector3(force.getX(), force.getY(), force.getZ()));
	}

	void PhysicsManager::detachPhysics()
	{
		for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				delete body->getMotionState();
			}
			dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

		for (int j = 0; j < collisionShapes->size(); j++)
		{
			btCollisionShape* shape = (*collisionShapes)[j];
			(*collisionShapes)[j] = 0;
			delete shape;
		}

		delete collisionShapes;

		delete dynamicsWorld;

		delete solver;

		delete overlappingPairCache;

		delete dispatcher;

		delete collisionConfiguration;

		collisionShapes->clear();

		entities.clear();
	}
}


