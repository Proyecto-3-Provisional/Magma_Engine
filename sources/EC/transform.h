#pragma once

#include <EC/component.h>
#include <EC/vector3D.h>


namespace magma_engine
{
	class Vector3D;

	class Transform : public ec::Component {
	public:
		Transform(){};

		virtual ~Transform() {};

		Vector3D& getPos();
		Vector3D& getForward();
		Vector3D getScale();


		void setPosition(Vector3D pos_);
		void setScale(Vector3D scale_);

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

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		void pitch(float deg);
		void yaw(float deg);
		void roll(float deg);

		// Establece la orientación de la entidad a un punto en el espacio
		void setDirection(Vector3D v);

		// Modificamos el vector forward para que apunte a un punto en el espacio, sobre el plano XZ
		void lookAtPoint(Vector3D target);


	private:

		Vector3D pos;
		Vector3D scale;
		// La direccion hacia delante en el eje z del objeto
		Vector3D forward;
	};
}

