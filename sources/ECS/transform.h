#pragma once

#include "vector3D.h"
#include "component.h"

class Transform : public ec::Component {
public:
	Transform() : pos(), vel() {};
	Transform(Vector3D pos_, Vector3D vel_) : pos(pos_), vel(vel_) {};

	virtual ~Transform() {};

	Vector3D& getPos();
	Vector3D& getVel();
	Vector3D getScale();
	void setPosition(Vector3D pos_);
	void setVelocity(Vector3D vel_);
	void setScale(Vector3D scale_);
	
	// w = width, eje X
	float getW() const;
	// h = height, eje Y
	float getH() const;
	// d = depth, eje Z
	float getD() const;

	// w = width, eje X
	void setW(float width_);
	// h = height, eje Y
	void setH(float height_);
	// d = depth, eje Z
	void setD(float depth_);

	virtual bool initComponent();
	virtual void update(float deltaTime);

	void pitch(float deg);
	void yaw(float deg);
	void roll(float deg);

private:
	Vector3D pos;
	Vector3D vel;
	Vector3D scale;
};