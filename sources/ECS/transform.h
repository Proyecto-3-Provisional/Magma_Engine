#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector3D.h"

class Component;

class Transform : public ecs::Component {
public:
	Transform() : pos(), vel(10,0,0){};
	Transform(Vector3D pos_, Vector3D vel_, float) : pos(pos_), vel(vel_) {};

	virtual ~Transform(){};

	inline Vector3D& getPos();
	inline Vector3D& getVel();
	inline Vector3D getScale();
	void setPosition(Vector3D pos_);
	void setVelocity(Vector3D vel_);
	void setScale(Vector3D scale_);

	float getW() const;
	float getH() const;
	void setW(float width_);
	void setH(float height_);

	virtual void update();
private:
	Vector3D pos;
	Vector3D vel;
	Vector3D scale;
};