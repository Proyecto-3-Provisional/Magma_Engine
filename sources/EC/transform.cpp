#include <EC/transform.h>
#include <EC/entity.h>


Vector3D& Transform::getPos()
{
	return pos;
}

Vector3D& Transform::getForward()
{
	return forward;
}

Vector3D Transform::getScale()
{
	return scale;
}

void Transform::setPosition(Vector3D pos_)
{
	pos = pos_;
}

//void Transform::setVelocity(Vector3D vel_)
//{
//	vel = vel_;
//}

void Transform::setScale(Vector3D scale_)
{
	scale = scale_;
}

void Transform::setVel(float v)
{
	vel = v;
}

float Transform::getW() const
{
	return scale.getX();
}

float Transform::getH() const
{
	return scale.getY();
}

float Transform::getD() const
{
	return scale.getZ();
}

void Transform::setW(float width_)
{
	scale.setX(width_);
}

void Transform::setH(float height_)
{
	scale.setY(height_);
}

void Transform::setD(float depth_)
{
	scale.setZ(depth_);
}

bool Transform::initComponent()
{
	pos = Vector3D(0, 0, 0);
	scale = Vector3D(1, 1, 1);
	forward = Vector3D(0, 0, 1);
	vel = 50;
	
	return true;
}

// movimiento entidad
void Transform::update(float deltaTime)
{
	pos = pos + forward * vel * deltaTime;
}

void Transform::pitch(float deg)
{
	Message m;
	m.id = _m_OBJECT_ROTATED;
	m.object_rotated_data = {deg, 'x'};
	ent->send(m);
}

void Transform::yaw(float deg)
{
	Message m;
	m.id = _m_OBJECT_ROTATED;
	m.object_rotated_data = { deg, 'y' };
	ent->send(m);
}

void Transform::roll(float deg)
{
	Message m;
	m.id = _m_OBJECT_ROTATED;
	m.object_rotated_data = { deg, 'z' };
	ent->send(m);
}

void Transform::setDirection(Vector3D v)
{
	forward = v.normalize();

	Message m;
	m.id = _m_OBJECT_LOOKAT;
	m.object_lookedat_data = { v.getX(), v.getY(), v.getZ()};
	ent->send(m);
}

void Transform::lookAtPoint(Vector3D target)
{

	setDirection(target - pos);
}
