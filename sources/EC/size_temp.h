#pragma once
//#include <EC/component.h>
#include <EC/vector3D.h>
//#include <Physics/rigidbody.h>
#include <EC/entity.h>


namespace magma_engine
{
	class Transform;
	class Rigidbody;
	
	class Size_Temp : public ec::Component
	{
	public:
		Size_Temp();
		virtual ~Size_Temp();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		void update(float deltaTime);

		float getTam();
		bool isPlayer();

		float tam = 1.0f;
		bool player = false;

	private:
		Transform* trPtr = nullptr;
		Rigidbody* rbPtr = nullptr;
		Vector3D originalScale;
	};
}