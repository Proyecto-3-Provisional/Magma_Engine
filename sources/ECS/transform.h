#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector3D.h"

class Component;

class Transform : public ecs::Component {
public:
	Transform() : pos(), vel(){};
	Transform(Vector3D pos_, Vector3D vel, float) : pos(), vel() {};

	//virtual bool init();

	virtual ~Transform(){};

	inline Vector3D& getPos();
	inline Vector3D& getVel();
	inline Vector3D getScale();
	void setPosition(Vector3D position);
	void setVelocity(Vector3D velocity);
	void setScale(Vector3D scale);

	float getW() const;
	float getH() const;
	void setW(float width);
	void setH(float height);

	virtual void update();/* {
		pos = pos + vel;
		std::cout << getPos().getX() << '\n';
	};*/
private:
	Vector3D pos;
	Vector3D vel;
	Vector3D scale_;
	/*Vector position_;
	Vector velocity_;*/
	//float rotation_; //en 3d me parece que esto no va a valer, cuaterniones?
};