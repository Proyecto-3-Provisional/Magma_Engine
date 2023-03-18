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

bool Transform::initComponent()
{
	pos = Vector3D(0, 0, 0);
	vel = Vector3D(0, 0, 0);
	scale = Vector3D(1, 1, 1);
	
	return true;
}

void Transform::update(float deltaTime)
{
	// movimiento entidad
	pos = pos + vel * deltaTime;
	
	// movimiento parte gráfica entidad
	///quitar///////////////ent->getGraphObj()->setPosition({ pos.getX(), pos.getY(), pos.getZ() });
}
