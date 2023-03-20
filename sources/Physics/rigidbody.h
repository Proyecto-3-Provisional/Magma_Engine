#pragma once

#include <iostream>
#include <vector>
#include "../ECS/component.h"
#include "../ECS/vector3D.h"

class Transform;

class Rigidbody : public ec::Component {
public:
	Rigidbody(Vector3D scale_);
	~Rigidbody() {};

	bool initComponent() override;
	void update(float deltaTime);

	int getIndex();
	void setIndex(int index_);

private:
	Transform* trPtr = nullptr;
	Vector3D scale;
	int index;
};