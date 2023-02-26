#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector_mag.h"

class Transform : public ecs::Component {
public:
	Transform() : pos(), vel(){};
	Transform(VectorMag pos_, VectorMag vel, float) : pos(), vel() {};

	virtual ~Transform(){};
	inline VectorMag& getPos() { return pos; };
	inline VectorMag& getVel() { return vel; };

	virtual void update();
private:
	VectorMag pos;
	VectorMag vel;
	/*Vector position_;
	Vector velocity_;*/
	//float rotation_; //en 3d me parece que esto no va a valer, cuaterniones?
};