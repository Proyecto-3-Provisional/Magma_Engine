#include "transform.h"
#include "entity.h"
#include "OgreSceneNode.h"

Vector3D& Transform::getPos()
{
	return pos;
}

Vector3D& Transform::getVel()
{
	return vel;
}

Vector3D Transform::getScale()
{
	return scale;
}

void Transform::setPosition(Vector3D pos_)
{
	pos = pos_;
}

void Transform::setVelocity(Vector3D vel_)
{
	vel = vel_;
}

void Transform::setScale(Vector3D scale_)
{
	scale = scale_;
}

float Transform::getW() const
{
	return scale.getX();
}

float Transform::getH() const
{
	return scale.getY();
}

void Transform::setW(float width_)
{
	scale.setX(width_);
}

void Transform::setH(float height_)
{
	scale.setY(height_);
}

void Transform::update()
{
	ent->getGraphObj()->setPosition({ pos.getX(), pos.getY(), pos.getZ() });

	if (abs(pos.getX()) > 500)
		vel = vel *  -1;
	pos = pos + vel;
}


