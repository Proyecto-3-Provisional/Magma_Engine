#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector3D.h"

class Transform : public ecs::Component {
public:
	Transform() : pos(), vel(){};
	Transform(Vector3D pos_, Vector3D vel, float) : pos(), vel() {};

	virtual ~Transform(){};
	inline Vector3D& getPos() { return pos; };
	inline Vector3D& getVel() { return vel; };

	virtual void update();
private:
	Vector3D pos;
	Vector3D vel;
	/*Vector position_;
	Vector velocity_;*/
	//float rotation_; //en 3d me parece que esto no va a valer, cuaterniones?
};