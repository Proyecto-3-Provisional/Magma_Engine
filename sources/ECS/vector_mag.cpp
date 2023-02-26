#include "vector_mag.h"

void VectorMag::setX(float x_)
{
	x = x_;
}

void VectorMag::setY(float y_)
{
	y = y_;
}

void VectorMag::setZ(float z_)
{
	z = z_;
}

void VectorMag::set(float x_, float y_, float z_)
{
	x = x_;
	y = y_;
	z = z_;
}

void VectorMag::set(const VectorMag& vmag_)
{
	x = vmag_.x;
	y = vmag_.y;
	z = vmag_.z;
}

void VectorMag::set(const VectorMag* vmag_)
{
	x = vmag_->x;
	y = vmag_->y;
	z = vmag_->z;
}

VectorMag& VectorMag::operator=(const VectorMag& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

VectorMag VectorMag::operator+(const VectorMag& v) const
{
	return VectorMag(x + v.x, y + v.y, z + v.z);
}
