#include <EC/init_factories.h>
#include <EC/factory_manager.h>

#include <EC/entity.h>
#include <EC/transform.h>

#include <Physics/rigidbody.h>

#include <Render/mesh.h>
#include <Render/button.h>
#include <Render/image.h>
#include <Render/text.h>

#include<Render/particle_system.h>
#include<Render/light.h>
#include<Render/camera.h>

#include <Sounds/audio_source.h>

namespace magma_engine
{
	Component* TransformFactory::createComponent(Entity* e)
	{
		return e->addComponent<Transform>();
	}

	Component* RigidbodyFactory::createComponent(Entity* e)
	{
		return e->addComponent<Rigidbody>();
	}

	Component* MeshFactory::createComponent(Entity* e)
	{
		return e->addComponent<Mesh>();
	}

	Component* AudioSourceFactory::createComponent(Entity* e)
	{
		return e->addComponent<AudioSource>();
	}

	Component* ButtonFactory::createComponent(Entity* e)
	{
		return e->addComponent<Button>();
	}

	Component* ImageFactory::createComponent(Entity* e)
	{
		return e->addComponent<Image>();
	}

	Component* TextFactory::createComponent(Entity* e)
	{
		return e->addComponent<Text>();
	}
	
	Component* ParticleSystemFactory::createComponent(Entity* e)
	{
		return e->addComponent<ParticleSystem>();
	}
	
	Component* LightFactory::createComponent(Entity* e)
	{
		return e->addComponent<Light>();
	}

	Component* CameraFactory::createComponent(Entity* e)
	{
		return e->addComponent<Camera>();
	}

	void setUpFactories()
	{
		FactoryManager::instance()->addFactory("Transform", new TransformFactory());
		FactoryManager::instance()->addFactory("Rigidbody", new RigidbodyFactory());
		FactoryManager::instance()->addFactory("Mesh", new MeshFactory());
		FactoryManager::instance()->addFactory("AudioSource", new AudioSourceFactory());
		FactoryManager::instance()->addFactory("Button", new ButtonFactory());
		FactoryManager::instance()->addFactory("Image", new ImageFactory());
		FactoryManager::instance()->addFactory("Text", new TextFactory());
		FactoryManager::instance()->addFactory("ParticleSystem", new ParticleSystemFactory());
		FactoryManager::instance()->addFactory("Light", new LightFactory());
		FactoryManager::instance()->addFactory("Camera", new CameraFactory());
	}
}

