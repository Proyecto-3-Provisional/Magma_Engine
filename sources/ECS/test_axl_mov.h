#pragma once

#include "transform.h"
#include "vector3D.h"

class TestAxlMov : public Transform {
public:
	TestAxlMov(Vector3D pos_, Vector3D vel_) : Transform(pos_, vel_) {};

	virtual void update();
};