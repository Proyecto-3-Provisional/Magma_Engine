#pragma once
#include <EC/factory.h>

namespace magma_engine
{
	struct Component;

	class TransformFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class RigidbodyFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class MeshFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class AudioSourceFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class ButtonFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class ImageFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class TextFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class ParticleSystemFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class LightFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	class CameraFactory : public Factory
	{
	public:
		Component* createComponent(Entity* e);
	};

	void setUpFactories();
}

