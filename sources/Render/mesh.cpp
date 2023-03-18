#include "mesh.h"

#include "../singleton.h"
#include "render_manager.h"

#include "../ECS/transform.h"
#include "../ECS/entity.h"

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
	trPtr = ent->getComponent<Transform>();
	if (trPtr == nullptr)
		return false;

	gObjPtr = RenderManager::instance()->addObject(gObjKey, nullptr, mesh, material);
	return (gObjPtr != nullptr);
}

void Mesh::update(float deltaTime)
{
	if (trPtr != nullptr)
	{
		Vector3D v = trPtr->getPos();
		gObjPtr->setPosition({ v.getX(), v.getY(), v.getZ() });
		Vector3D s = trPtr->getScale();
		gObjPtr->setScale({ s.getX(), s.getY(), s.getZ() });
	}
}

void Mesh::render() // planteárselo...
{
}
