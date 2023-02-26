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
	return scale_;
}

void Transform::setPosition(Vector3D position)
{
	pos = position;
}

void Transform::setVelocity(Vector3D velocity)
{
	vel = velocity;
}

void Transform::setScale(Vector3D scale)
{
	scale_ = scale;
}

float Transform::getW() const
{
	return scale_.getX();
}

float Transform::getH() const
{
	return scale_.getY();
}

void Transform::setW(float width)
{
	scale_.setX(width);
}

void Transform::setH(float height)
{
	scale_.setY(height);
}

void Transform::update()
{
	//ent_->getOgreNode()->setPosition(x, y, z);
	pos = pos + vel;
	std::cout << getPos().getX() << '\n';
}


