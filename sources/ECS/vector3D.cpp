#include "vector3D.h"

void Vector3D::setX(float x_)
{
	x = x_;
}

void Vector3D::setY(float y_)
{
	y = y_;
}

void Vector3D::setZ(float z_)
{
	z = z_;
}

void Vector3D::set(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

void Vector3D::set(const Vector3D& vmag_)
{
	x = vmag_.x;
	y = vmag_.y;
	z = vmag_.z;
}

void Vector3D::set(const Vector3D* vmag_)
{
	x = vmag_->x;
	y = vmag_->y;
	z = vmag_->z;
}

Vector3D& Vector3D::operator=(const Vector3D& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

Vector3D Vector3D::operator+(const Vector3D& v) const
{
	return Vector3D(x + v.x, y + v.y, z + v.z);
}
