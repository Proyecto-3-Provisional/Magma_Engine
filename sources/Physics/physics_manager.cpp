#include "physics_manager.h"
#include <iostream>
#include <stdio.h>

PhysicsManager::PhysicsManager() : collisionConfiguration(nullptr), dispatcher(nullptr), overlappingPairCache(nullptr), solver(nullptr), dynamicsWorld(nullptr)
{
}

PhysicsManager::~PhysicsManager()
{
}

// Inicia la clase y el mundo físico de PhysicsManager
int PhysicsManager::initPhysics()
{
	// Configuración de colisión: contiene la configuración predeterminada para la memoria
	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	overlappingPairCache = new btDbvtBroadphase();

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, 0, 0));

	return 1;
}

// Añadir un rigidbody a la escena con forma cúbica
btRigidBody* PhysicsManager::addRigidBody(const double& xShape, const double& yShape, const double& zShape, const double& xTransform, const double& yTransform, const double& zTransform)
{
	btCollisionShape* rigidBodyShape = new btBoxShape(btVector3(btScalar(xShape), btScalar(yShape), btScalar(zShape)));

	collisionShapes.push_back(rigidBodyShape);

	btTransform newRigidBody;
	newRigidBody.setIdentity();
	newRigidBody.setOrigin(btVector3(xTransform, yTransform, zTransform));

	btScalar mass(1.);

	/// El objeto es dinamico si la masa es distinta a zero, en el caso contrario seria estatico
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);

	if (isDynamic)
		rigidBodyShape->calculateLocalInertia(mass, localInertia);

	// El uso de MotionState es opcional, proporciona capacidades de interpolación y solo sincroniza objetos 'activos'
	btDefaultMotionState* myMotionState = new btDefaultMotionState(newRigidBody);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, rigidBodyShape, localInertia);

	btRigidBody* body = new btRigidBody(rbInfo);

	body->setUserIndex(dynamicsWorld->getNumCollisionObjects());
	//body->setUserIndex(lastUserIndex);
	//lastUserIndex++;

	// Añadir el cuerpo al mundo de la dinámica
	dynamicsWorld->addRigidBody(body);
	return body;
}

// Borra un rigidbody dado su índice
void PhysicsManager::deleteRigidBody(int userIndex)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[userIndex];
	btRigidBody* body = btRigidBody::upcast(obj);
	if (body && body->getMotionState())
	{
		delete body->getMotionState();
	}
	dynamicsWorld->removeCollisionObject(obj);
	delete obj;

	// Al borrar la entidad se rellena el hueco del array con el último elemento. Actualizamos su índice:  
	btCollisionObject* obj1 = dynamicsWorld->getCollisionObjectArray()[userIndex];
	btRigidBody* body1 = btRigidBody::upcast(obj1);
	body1->setUserIndex(userIndex);
}

// Actualiza el estado de los rigidbody
void PhysicsManager::update()
{
	dynamicsWorld->stepSimulation(1.f / 60.f, 10);

	updateCollisions();

	for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		// Por si no añadireamos MotionState
		//else
		//{
		//	trans = obj->getWorldTransform();
		//}

		// Muestra la posición de todos los rigidbody  por consola
		printf("world pos object %d = %f,%f,%f\n", obj->getUserIndex(), float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}
}

// Muestra los pares de objetos que colisionan
void PhysicsManager::updateCollisions()
{
	// Obtenemos la lista de colisiones por pares
	btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

	// Iteramos sobre cada par de colisiones
	for (int i = 0; i < collisionPairs.size(); ++i) {
		btBroadphasePair& collisionPair = collisionPairs[i];

		// Obtenemos los cuerpos rígidos que han colisionado
		btRigidBody* body1 = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
		btRigidBody* body2 = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

		// Verificamos que ambos cuerpos rígidos existan y que no sean estáticos (para evitar falsos positivos)
		if (body1 && body2 && body1->getInvMass() > 0.0f && body2->getInvMass() > 0.0f) {

			// Verificamos que los cuerpos tengan indices de usuario asignados
			if (body1->getUserIndex() == -1 || body2->getUserIndex() == -1) {
				std::cout << "Al menos uno de los objetos no tiene índice de usuario asignado" << std::endl;
				continue;
			}

			// Verificamos que los cuerpos sean distintos
			if (body1->getUserIndex() == body2->getUserIndex()) {
				std::cout << "Los objetos son iguales" << std::endl;
				continue;
			}

			std::cout << "Colisión detectada entre objetos " << body1->getUserIndex() << " y " << body2->getUserIndex() << std::endl;
		}
	}
}

// Comprueba si dos rigidbody en concreto colisionan
bool PhysicsManager::isCollide(int index1, int index2)
{
	btCollisionObject* obj1 = dynamicsWorld->getCollisionObjectArray()[index1];
	btRigidBody* body1 = btRigidBody::upcast(obj1);
	btCollisionObject* obj2 = dynamicsWorld->getCollisionObjectArray()[index2];
	btRigidBody* body2 = btRigidBody::upcast(obj2);

	// Obtenemos la lista de colisiones por pares
	btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

	bool colision = false;
	for (int i = 0; i < collisionPairs.size(); ++i) {
		btBroadphasePair& collisionPair = collisionPairs[i];

		// Obtenemos los cuerpos rígidos que han colisionado
		btRigidBody* body1Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
		btRigidBody* body2Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

		// Verificamos que ambos cuerpos rígidos existan y que no sean estáticos (para evitar falsos positivos)
		if (body1Pair && body2Pair && body1Pair->getInvMass() > 0.0f && body2Pair->getInvMass() > 0.0f) {
			// Comprobamos si el par que colisiona es el que buscamos 
			if ((body1 == body1Pair && body2 == body2Pair) || (body2 == body1Pair && body1 == body2Pair)) {
				colision = true;
				break;
			}
		}
	}

	return colision;
}

// Devuelve un vector con los índices de los rigidbody que colisionan con index   
std::vector<int> PhysicsManager::getArrayOfIndexColliders(int index)
{
	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[index];
	btRigidBody* body = btRigidBody::upcast(obj);

	// Obtenemos la lista de colisiones por pares
	btBroadphasePairArray& collisionPairs = dynamicsWorld->getPairCache()->getOverlappingPairArray();

	std::vector<int> colliders;
	for (int i = 0; i < collisionPairs.size(); ++i) {
		btBroadphasePair& collisionPair = collisionPairs[i];

		// Obtenemos los cuerpos rígidos que han colisionado
		btRigidBody* body1Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy0->m_clientObject);
		btRigidBody* body2Pair = static_cast<btRigidBody*>(collisionPair.m_pProxy1->m_clientObject);

		// Verificamos que ambos cuerpos rígidos existan y que no sean estáticos (para evitar falsos positivos)
		if (body1Pair && body2Pair && body1Pair->getInvMass() > 0.0f && body2Pair->getInvMass() > 0.0f) {

			// Si alguno del par de colision es el indice principal guardamos la informacion del indice que hemos colisionado
			if (body == body1Pair) colliders.push_back(body2Pair->getUserIndex());
			else if(body == body2Pair) colliders.push_back(body1Pair->getUserIndex());
		}
	}

	return colliders;
}

// Eliminacion de objetos de la clase PhysicsManager
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

	// Borra los rigidbody
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	delete dynamicsWorld;

	delete solver;

	delete overlappingPairCache;

	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();
}
