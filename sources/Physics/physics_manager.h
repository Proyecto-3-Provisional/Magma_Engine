#pragma once
#include "btBulletDynamicsCommon.h"
#include <vector>

class PhysicsManager {
public:
	PhysicsManager();
	~PhysicsManager();

	int initPhysics();
	btRigidBody* addRigidBody(const double& xShape, const double& yShape, const double& zShape, const double& xTransform, const double& yTransform, const double& zTransform);
	void deleteRigidBody(const int& userIndex);
	void deleteRigidBodies(std::vector<int>& vIndex);
	void update();
	void updateCollisions();
	bool isCollide(const int& index1, const int& index2);
	std::vector<int> getArrayOfIndexColliders(int index);
	void detachPhysics();


private:
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btBroadphaseInterface* overlappingPairCache;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;


	btAlignedObjectArray<btCollisionShape*> collisionShapes;
	//int lastUserIndex = 0;
};