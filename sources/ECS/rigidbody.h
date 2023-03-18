#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector3D.h"

class Rigidbody : public ec::Component {
public:
	Rigidbody(Vector3D scale_, Vector3D pos_);
	~Rigidbody() {};

	bool initComponent() override;

private:
	Vector3D scale;
	Vector3D pos;
	int index;
};