#include "init_factories.h"
#include "factory_manager.h"
#include "../EC/transform.h"
#include "../Physics/rigidbody.h"
#include "../Render/mesh.h"

ec::Component* TransformFactory::createComponent(ec::Entity* e)
{
	return new Transform();
}

ec::Component* RigidbodyFactory::createComponent(ec::Entity* e)
{
	//return new Rigidbody();
}

ec::Component* MeshFactory::createComponent(ec::Entity* e)
{
	return new Mesh();
}

void setUpFactories() 
{
	FactoryManager::instance()->addFactory(new TransformFactory());
	//FactoryManager::instance()->addFactory("Transform", new TransformFactory());
	//FactoryManager::instance()->addFactory("Rigidbody", new RigidbodyFactory());
	//FactoryManager::instance()->addFactory("Mesh", new MeshFactory());
}

