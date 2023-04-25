#include <EC/transform.h>
#include <EC/entity.h>

namespace magma_engine
{
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

	void Transform::setScale(Vector3D scale_)
	{
		scale = scale_;
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

	bool Transform::initComponent(Vector3D pos_, Vector3D scale_)
	{
		try {
			pos = pos_;
			scale = scale_;
			forward = Vector3D(0, 0, 1);
		}
		catch (...) {
			return false;
		}

		return true;
	}

	void Transform::pitch(float deg)
	{
		Message m;
		m.id = _m_OBJECT_ROTATED;
		m.object_rotated_data = { deg, 'x' };
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
		m.object_lookedat_data = { v.getX(), v.getY(), v.getZ() };
		ent->send(m);
	}

	void Transform::lookAtPoint(Vector3D target)
	{

		setDirection(target - pos);
	}
}

