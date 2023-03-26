#pragma once

#include <iostream>
#include <vector>
#include "../EC/component.h"
#include "../EC/vector3D.h"

class Transform;
class btRigidBody;

class Rigidbody : public ec::Component {
public:
	Rigidbody(const Vector3D& scale_);
	~Rigidbody();

	bool initComponent() override;
	void update(float deltaTime) override;

	bool isOnCollision();
	bool isCollideWith(int indexCollide);

	void addForce(const Vector3D& force);
	int getIndex();

private:
	Transform* trPtr = nullptr;
	btRigidBody* rigidPtr = nullptr;
	Vector3D scale;
};