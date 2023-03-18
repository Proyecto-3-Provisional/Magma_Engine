#pragma once

#include "../ECS/component.h"
#include "../ECS/vector3D.h"
#include "graphical_object.h"

class Mesh : public ec::Component {
public:
	Mesh();
	virtual ~Mesh();

	GraphicalObject* getObj();

	bool initComponent(std::string name, std::string mesh = "", std::string material = "default");
	void update(float deltaTime);
	void render();

private:
	GraphicalObject* gObjPtr = nullptr;
};