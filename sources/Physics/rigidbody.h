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
		// Determina si el objeto se encuentra en colisión con otros objetos
		bool isOnCollision(); 
		// Devuelve todos los objetos que colisionan con este rigidbody
		std::vector<Entity*> getCollisionObjs(); 
		// Detectar colision con otro objeto cuyo índice se proporciona como parámetro
		bool isCollideWith(int indexCollide); 
		// Aplica una fuerza al objeto
		void addForce(const Vector3D& force);
		// Devuelve el índice del objeto
		int getIndex(); 

		void setLinearDamping(float d);
		void setAngularDamping(float d);

		Vector3D getVelocity();

	private:

		Transform* trPtr = nullptr;
		Mesh* meshPtr;
		btRigidBody* rigidPtr = nullptr;
		Vector3D proportions;
		float mass;
		float linearDamping;
		float angularDamping;
	};
}

