#pragma once

#include <iostream>
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
		Rigidbody(const Vector3D& scale_);
		~Rigidbody();

		bool initComponent() override;
		void update(float deltaTime) override;

		bool isOnCollision();
		bool isCollideWith(int indexCollide);

		void addForce(const Vector3D& force);
		int getIndex();

	private:

		Transform* trPtr = nullptr;
		btRigidBody* rigidPtr = nullptr;
		Vector3D scale;
	};
}

