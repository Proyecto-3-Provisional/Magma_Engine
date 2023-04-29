#pragma once

namespace magma_engine {
	class Quaternion {
	public:
		Quaternion();
		Quaternion(float x_, float y_, float z_, float w_);
		Quaternion(const Quaternion& q);
		~Quaternion() {};

		inline float getX() const { return x; }
		inline float getY() const { return y; }
		inline float getZ() const { return z; }
		inline float getW() const { return w; }

	private:
		float x;
		float y;
		float z;
		float w;
	};
}