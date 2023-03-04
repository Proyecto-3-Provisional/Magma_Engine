#pragma once

#include <iostream>
#include <vector>
#include "component.h"
#include "vector3D.h"

class Component;

class Transform : public ec::Component {
public:
	Transform() : pos(), vel(){};
	Transform(Vector3D pos_, Vector3D vel_) : pos(pos_), vel(vel_) {};

	virtual ~Transform(){};

	Vector3D& getPos();
	Vector3D& getVel();
	Vector3D getScale();
	void setPosition(Vector3D pos_);
	void setVelocity(Vector3D vel_);
	void setScale(Vector3D scale_);

	float getW() const;
	float getH() const;
	void setW(float width_);
	void setH(float height_);

	virtual void update(float deltaTime);
private:
	Vector3D pos;
	Vector3D vel;
	Vector3D scale;
};