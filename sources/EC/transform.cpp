#include <EC/transform.h>
#include <EC/entity.h>

#include <iostream>
#include <exception>

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

	
	bool Transform::initComponent(std::map<std::string, std::string> args)
	{
		try {
			Vector3D v = Vector3D(stof(args["PositionX"]), stof(args["PositionY"]), stof(args["PositionZ"]));
			Vector3D s = Vector3D(stof(args["ScaleX"]), stof(args["ScaleY"]), stof(args["ScaleZ"]));

			pos = v;
			scale = s;
			forward = Vector3D(0, 0, 1);
		}
		catch (...) {
			return false;
		}

		return true;
	}

	bool Transform::start()
	{
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
	}

	void Transform::lookAtPoint(Vector3D target)
	{

		setDirection(target - pos);
	}
}

