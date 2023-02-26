#pragma once

#include <cmath>

class VectorMag {
public:
	VectorMag() : x(), y(), z() {};
	VectorMag(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
	VectorMag(const VectorMag& vmag) : x(vmag.getX()), y(vmag.getY()), z(vmag.getZ()) {};
	~VectorMag() {};


	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline float getZ() const { return z; }

	void setX(float x_);
	void setY(float y_);
	void setZ(float z_);

	void set(float x_, float y_, float z_);
	void set(const VectorMag& vmag_);
	void set(const VectorMag* vmag_);

	// copy assignment
	VectorMag& operator=(const VectorMag& v);

	//// length of the vector
	//inline float magnitude() const {
	//	return sqrtf(powf(x_, 2) + powf(y_, 2));
	//}

	//// vector in the same direction of length 1
	//inline Vector2D normalize() const {
	//	return *this / magnitude();
	//}

	// counter clockwise rotation in a normal coordinate system, and
	// it is clockwise rotation if we work with a coordinate system
	// in which the vertical axe is flipped (it is like a mirror over
	// the horizontal axe)-- which the case when working with the SDL.
	//
	//Vector2D rotate(float degrees) const;

	// Computes the angle between 'this' and 'v'. The result is
	// between -180 and 180, and is such that the following holds:
	//
	//   this->rotate(angle) == v
	//
	//float angle(const Vector2D& v) const;

	//// vector subtraction
	//inline Vector2D operator-(const Vector2D& v) const {
	//	return Vector2D(x_ - v.x_, y_ - v.y_);
	//}

	// vector addition
	VectorMag operator+(const VectorMag& v) const;

	//// multiplication by constant (scaling)
	//inline Vector2D operator*(float d) const {
	//	return Vector2D(x_ * d, y_ * d);
	//}

	//// division by constant (scaling)
	//inline Vector2D operator/(float d) const {
	//	return Vector2D(x_ / d, y_ / d);
	//}

	//// scalar multiplication
	//inline float operator *(const Vector2D& d) const {
	//	return d.x_ * x_ + d.y_ * y_;
	//}
private:
	float x;
	float y;
	float z;
};