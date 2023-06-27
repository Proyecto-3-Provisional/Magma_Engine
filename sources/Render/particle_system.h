#pragma once

#include <EC/component.h>
//#include <OgreSceneManager.h>
//#include <OgreSceneNode.h>
#include <Render/render_manager.h>
//#include <OgreParticleSystem.h>
#include <iostream>

namespace Ogre {
	class ParticleSystem;
}

namespace magma_engine
{
	class Mesh;

	class ParticleSystem : public Component
	{
	public:
		ParticleSystem();
		
		virtual ~ParticleSystem();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();

		void update(float deltaTime);

		//Esto es para que otros componentes puedan activar y desactivar la emision del sistema
		//y es lo que va a usar PlayerController para que salgan las burbujas cuando se mueva
		void emisionControl(bool activate);

	private:
		//El sistema de particulas lo uniremos al nodo de la escena de mesh de la entidad para que se emiten las
		//particulas dondequiera que este la entidad durante la partida
		magma_engine::Mesh* meshptr = nullptr;

		Ogre::ParticleSystem* particleSystem = nullptr;

		float emisionTime; //este es el tiempo que queremos que dure la emision
		float emisionDuration; //esto es la duracion de la emision 

	};
}

