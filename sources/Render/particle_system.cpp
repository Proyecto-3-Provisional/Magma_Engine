#include <Render/particle_system.h>
#include <EC/entity.h>
#include <Render/mesh.h>
#include <Render/graphical_object.h>
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>


namespace magma_engine
{
	ParticleSystem::ParticleSystem() : Component(), emisionTime(0.0f), emisionDuration(0.0f) {}

	ParticleSystem::~ParticleSystem() 
	{
		magma_engine::RenderManager::instance()->getSceneManager()->destroyParticleSystem(particleSystem);
		particleSystem = nullptr;
		meshptr = nullptr;
	}

	bool ParticleSystem::initComponent(std::map<std::string, std::string> args)
	{
		try {
			particleSystem = magma_engine::RenderManager::instance()->getSceneManager()->createParticleSystem(args["name"], args["psName"]);
			emisionTime = stof(args["psTime"]);
			if (particleSystem == nullptr)
			{
				std::cout << "WARNING! - error al crear el sistema de particulas \n";
				return false;
			}
		}
		catch (std::exception& e) {
			std::cout << "WARNING! - error en un componente particle_system:\n\n     " << e.what() << "\n\n";

			return false;
		}
		return true;
	}

	bool ParticleSystem::start()
	{
		particleSystem->setEmitting(false);
		meshptr = ent->getComponent<Mesh>();
		if (meshptr == nullptr)
		{
			std::cout << "ParticleSystem is missing mesh";
			return false;
		}

		meshptr->getObj()->getNode()->attachObject(particleSystem);
		emisionDuration = emisionTime;

		return true;
	}

	void ParticleSystem::update(float deltaTime) 
	{
		//std::cout << "AAAAAAAAAAAAAAAAAAAAAAA";
		if (particleSystem->getEmitting()) {
			if (emisionDuration < 0.0f) {
				particleSystem->setEmitting(false);
				emisionDuration = emisionTime;
			}
			else
				emisionDuration -= deltaTime;

		}
		/*else
		{
			if (emisionDuration < 0.0f)
			{
				particleSystem->setEmitting(true);
				emisionDuration = emisionTime;
			}
			else
				emisionDuration -= deltaTime;
		}*/
	}

	void ParticleSystem::emisionControl(bool activate)
	{
		if(particleSystem != nullptr)
			particleSystem->setEmitting(activate);
	}
}