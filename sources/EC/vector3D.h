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
	void set(const Vector3D* v_);

	// tarea de copia
	Vector3D& operator=(const Vector3D& v);
	Vector3D& operator+=(const Vector3D& v);

	// longitud del vector
	float magnitude() const;

	// vector en la misma dirección que length 1.
	Vector3D normalize() const;

	// resta del vector
	Vector3D operator-(const Vector3D& v) const;

	// suma del vector
	Vector3D operator+(const Vector3D& v) const;

	// multiplicación por constante
	Vector3D operator*(float d) const;

	// división por constante
	Vector3D operator/(float d) const;

	// multiplicación escalar
	float operator *(const Vector3D& d) const;

private:
	float x;
	float y;
	float z;
};