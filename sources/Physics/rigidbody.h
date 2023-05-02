#pragma once

#include <iostream>
#include <vector>
#include <EC/component.h>
#include <EC/vector3D.h>
#include <map>

class btRigidBody;

namespace magma_engine
{
	class Transform;
	class Mesh;

	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		virtual void update(float deltaTime) override;

		bool isOnCollision(); // Determina si el objeto se encuentra en colisi�n con otros objetos
		std::vector<Entity*> getCollisionObjs(); // Devuelve todos los objetos que colisionan con este rigidbody
		bool isCollideWith(int indexCollide); // Detectar colision con otro objeto cuyo �ndice se proporciona como par�metro

		void addForce(const Vector3D& force); // Aplica una fuerza al objeto
		int getIndex(); // Devuelve el �ndice del objeto

		void setLinearDamping(float d);
		void setAngularDamping(float d);

		Vector3D getVelocity();

	private:

		Transform* trPtr = nullptr;
		Mesh* meshPtr;
		btRigidBody* rigidPtr = nullptr;
		Vector3D proportions;
		float linearDamping;
		float angularDamping;
	};
}

