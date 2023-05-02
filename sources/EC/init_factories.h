#pragma once
#include <EC/factory.h>

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

	class ProgressBarFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class TimerFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class PlayerControllerFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class EnemyControllerFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	class Size_TempFactory : public Factory
	{
	public:
		ec::Component* createComponent(ec::Entity* e);
	};

	void setUpFactories();
}

