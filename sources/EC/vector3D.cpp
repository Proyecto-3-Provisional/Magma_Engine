#include <EC/vector3D.h>

namespace magma_engine
{
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

	void Vector3D::set(const Vector3D& v_)
	{
		x = v_.x;
		y = v_.y;
		z = v_.z;
	}

	void Vector3D::set(const Vector3D* v_)
	{
		x = v_->x;
		y = v_->y;
		z = v_->z;
	}

	Vector3D& Vector3D::operator=(const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector3D& Vector3D::operator+=(const Vector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	float Vector3D::magnitude() const
	{
		return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
	}

	Vector3D Vector3D::normalize() const
	{
		return *this / magnitude();
	}

	Vector3D Vector3D::operator-(const Vector3D& v) const
	{
		return Vector3D(x - v.x, y - v.y, z - v.z);
	}

	Vector3D Vector3D::operator+(const Vector3D& v) const
	{
		return Vector3D(x + v.x, y + v.y, z + v.z);
	}

	Vector3D Vector3D::operator*(float d) const
	{
		return Vector3D(x * d, y * d, z * d);
	}

	Vector3D Vector3D::operator/(float d) const
	{
		return Vector3D(x / d, y / d, z / d);
	}

	float Vector3D::operator *(const Vector3D& d) const
	{
		return d.x * x + d.y * y + d.z * z;
	}
}


