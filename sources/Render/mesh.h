#pragma once

#include <EC/component.h>
#include <EC/quaternion.h>

namespace magma_engine
{
	class Transform;
	class GraphicalObject;

	class Mesh : public Component
	{
	public:
		Mesh();
		virtual ~Mesh();

		GraphicalObject* getObj();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		void update(float deltaTime);
		void render();

		void recieve(const Message&) override;

		//axis char: 'x', 'y' or 'z'
		void rotate(float deg, char axis);
		void setDirection(float x, float y, float z);

		Vector3D getProportions();
		Quaternion getOrientation();

		void setVisible(bool visible);

	private:

		GraphicalObject* gObjPtr = nullptr;
		Transform* trPtr = nullptr;
	};
}
