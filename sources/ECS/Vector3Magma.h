#pragma once

class Vector3Magma
{
public:
	Vector3Magma(){};
	Vector3Magma(const Vector3Magma& v3m);
	Vector3Magma(float vmx, float vmy, float vmz);

	inline float getX() { return vmx; }
	inline float getY() { return vmy; }
	inline float getZ() { return vmz; }

	inline float setX(float x) { vmx = x; }
	inline float setY(float y) { vmy = y; }
	inline float setZ(float z) { vmz = z; }

private:
	float vmx;
	float vmy;
	float vmz;
};

