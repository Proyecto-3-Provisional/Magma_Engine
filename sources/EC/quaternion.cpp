#include <EC/quaternion.h>

namespace magma_engine {
	Quaternion::Quaternion() : x(), y(), z(), w() {};
	Quaternion::Quaternion(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {};
	Quaternion::Quaternion(const Quaternion& q) : x(q.getX()), y(q.getY()), z(q.getZ()), w(q.getW()) {};
}