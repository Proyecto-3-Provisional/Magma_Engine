#include <Magma/init_factories.h>
#include <Magma/factory_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>

#include <Physics/rigidbody.h>

#include <Render/mesh.h>

ec::Component* TransformFactory::createComponent(ec::Entity* e)
{
	return e->addComponent<Transform>();
}

ec::Component* RigidbodyFactory::createComponent(ec::Entity* e)
{
	return e->addComponent<Rigidbody>();
}

ec::Component* MeshFactory::createComponent(ec::Entity* e)
{
	return e->addComponent<Mesh>();
}

void setUpFactories() 
{
	FactoryManager::instance()->addFactory("Transform", new TransformFactory());
	FactoryManager::instance()->addFactory("Rigidbody", new RigidbodyFactory());
	FactoryManager::instance()->addFactory("Mesh", new MeshFactory());
}

