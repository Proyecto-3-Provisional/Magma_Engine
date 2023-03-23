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
		/*Vector3D d = trPtr->getDir();
		gObjPtr->setDirection({d.getX(), d.getY(), d.getZ()});*/
	}
}

void Mesh::render() // planteárselo...
{
}

void Mesh::recieve(const Message& m)
{
	switch (m.id)
	{
	case _m_OBJECT_ROTATED:
		rotate(m.object_rotated_data.deg, m.object_rotated_data.axis);
	default:
		break;
	}
}

void Mesh::rotate(float deg, char axis)
{
	switch (axis)
	{
	case 'x':
		getObj()->pitch(deg);
		break;
	case 'y':
		getObj()->yaw(deg);
		break;
	case 'z':
		getObj()->roll(deg);
		break;
	default:
		break;
	}
}
