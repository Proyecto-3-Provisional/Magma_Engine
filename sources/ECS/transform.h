#pragma once

#include <iostream>

#include "component.h"
#include "Vector3Magma.h"

class Transform : public Component {
public:
	Transform(){};
	Transform(Vector3Magma){};
	virtual ~Transform(){};
	inline Vector3Magma& getPos(){};
	inline Vector3Magma& getVel(){}; //queremos que nuestro transform tenga esto? seguramente para fisicas o algo

	virtual void update() {
		std::cout << "seguimos con EC\n";
	}
private:
	Vector3Magma position_;
	Vector3Magma velocity_;
	float width_;
	float height_;
	float rotation_; //en 3d me parece que esto no va a valer, cuaterniones?
};