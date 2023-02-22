#pragma once

#include <iostream>

#include "component.h"

class Transform : public Component {
public:
	Transform(){};
	//Transform(/*Vector*/){};
	virtual ~Transform(){};
	//inline Vector& getPos(){};
	//inline Vector& getVel(){}; //queremos que nuestro transform tenga esto? seguramente para fisicas o algo

	virtual void update() {
		std::cout << "seguimos con EC\n";
	}
private:
	/*Vector position_;
	Vector velocity_;*/
	float width_;
	float height_;
	float rotation_; //en 3d me parece que esto no va a valer, cuaterniones?
};