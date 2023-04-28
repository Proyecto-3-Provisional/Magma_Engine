#pragma once

#include <iostream>
#include <vector>
#include <EC/component.h>
#include <EC/vector3D.h>

class btRigidBody;

namespace magma_engine
{
	class Transform;

	class Rigidbody : public ec::Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		bool initComponent(const Vector3D& scale_);
		void update(float deltaTime) override;

		bool isOnCollision(); // Determina si el objeto se encuentra en colisión con otros objetos
		std::vector<int> getCollisionObjs(); // Devuelve todos los objetos que colisionan con este rigidbody
		bool isCollideWith(int indexCollide); // Detectar colision con otro objeto cuyo índice se proporciona como parámetro

		void addForce(const Vector3D& force); // Aplica una fuerza al objeto
		int getIndex(); // Devuelve el índice del objeto

	private:

		Transform* trPtr = nullptr;
		btRigidBody* rigidPtr = nullptr;
		Vector3D scale;
	};
}

