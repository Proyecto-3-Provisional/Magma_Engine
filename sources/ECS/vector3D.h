#pragma once

#include <cmath>

class Vector3D {
public:
	Vector3D() : x(), y(), z() {};
	Vector3D(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {};
	Vector3D(const Vector3D& vmag) : x(vmag.getX()), y(vmag.getY()), z(vmag.getZ()) {};
	~Vector3D() {};


	inline float getX() const { return x; }
	inline float getY() const { return y; }
	inline float getZ() const { return z; }

	void setX(float x_);
	void setY(float y_);
	void setZ(float z_);
		void set(float x_, float y_, float z_);
	void set(const Vector3D& v_);
	//inline void set(const Vector3D&& v_);
	void set(const Vector3D* v_);

	// copy assignment
	Vector3D& operator=(const Vector3D& v);
	Vector3D& operator+=(const Vector3D& v);

	// length of the vector
	float magnitude() const;

	// vector in the same direction of length 1
	Vector3D normalize() const;

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

	// vector subtraction
	Vector3D operator-(const Vector3D& v) const;

	// vector addition
	Vector3D operator+(const Vector3D& v) const;

	// multiplication by constant (scaling)
	Vector3D operator*(float d) const;

	// division by constant (scaling)
	Vector3D operator/(float d) const;

	// scalar multiplication
	float operator *(const Vector3D& d) const;
private:
	float x;
	float y;
	float z;
};