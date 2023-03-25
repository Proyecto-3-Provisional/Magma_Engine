#pragma once

#include "../ECS/component.h"
#include "../ECS/vector3D.h"
#include "graphical_object.h"

class Transform;

class Mesh : public ec::Component {
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