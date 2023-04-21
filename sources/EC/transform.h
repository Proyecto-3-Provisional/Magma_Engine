#pragma once

#include <EC/vector3D.h>
#include <EC/component.h>

namespace magma_engine
{
	class Transform : public ec::Component {
	public:
		Transform() : pos(), vel() {};
		Transform(Vector3D pos_, float vel_) : pos(pos_), vel(vel_) {};

		virtual ~Transform() {};

		Vector3D& getPos();
		Vector3D& getForward();
		Vector3D getScale();


		void setPosition(Vector3D pos_);
		void setScale(Vector3D scale_);
		void setVel(float v);

		// w = width, eje X
		float getW() const;
		// h = height, eje Y
		float getH() const;
		// d = depth, eje Z
		float getD() const;

		// w = width, eje X
		void setW(float width_);
		// h = height, eje Y
		void setH(float height_);
		// d = depth, eje Z
		void setD(float depth_);

		virtual bool initComponent();
		virtual void update(float deltaTime);

		void pitch(float deg);
		void yaw(float deg);
		void roll(float deg);

		void setDirection(Vector3D v);

		//Modificamos el vector forward para que apunte a un punto en el espacio, sobre el plano XZ
		void lookAtPoint(Vector3D target);


	private:

		Vector3D pos;
		Vector3D scale;
		//La direccion hacia delante en el eje z del objeto
		Vector3D forward;

		float vel;
	};
}

