#pragma once
#include <Magma/factory.h>

namespace magma_engine
{
	struct ec::Component;

	class TransformFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class RigidbodyFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class MeshFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class AudioSourceFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class ButtonFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class ImageFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class TextFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	void setUpFactories();
}

