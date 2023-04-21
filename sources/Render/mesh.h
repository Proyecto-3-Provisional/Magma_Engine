#pragma once

#include <EC/component.h>

namespace magma_engine
{
	class Transform;
	class GraphicalObject;

	class Mesh : public ec::Component
	{
	public:
		Mesh();
		virtual ~Mesh();

		GraphicalObject* getObj();

		bool initComponent(std::string name, std::string mesh = "", std::string material = "default");
		void update(float deltaTime);
		void render();

		void recieve(const Message&) override;

		//axis char: 'x', 'y' or 'z'
		void rotate(float deg, char axis);
		void setDirection(float x, float y, float z);


	private:

		GraphicalObject* gObjPtr = nullptr;
		Transform* trPtr = nullptr;
	};
}

