#include "mesh.h"

#include "../singleton.h"
#include "render_manager.h"

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
	/*bool success = */RenderManager::instance()->removeObject(gObjPtr);
}

GraphicalObject* Mesh::getObj()
{
	return gObjPtr;
}

bool Mesh::initComponent(std::string gObjKey, std::string mesh, std::string material)
{
	gObjPtr = RenderManager::instance()->addObject(gObjKey, nullptr, mesh, material);
	return (gObjPtr != nullptr);
}

void Mesh::update(float deltaTime)
{
}

void Mesh::render() // planteárselo...
{
}
