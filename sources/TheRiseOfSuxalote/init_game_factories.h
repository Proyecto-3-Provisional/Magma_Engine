#pragma once

#ifdef SUXALOTE_EXPORTS
#define SUXALOTE_API __declspec(dllexport)
#else
#define SUXALOTE_API __declspec(dllimport)
#endif

#include <EC/factory.h>

namespace magma_engine
{
	class FactoryManager;
}

namespace magma_game
{
	struct magma_engine::Component;

	class ProgressBarFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class TimerFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class PlayerControllerFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class EnemyControllerFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class SizeTempFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class PowerUpFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	class EndgameFactory : public magma_engine::Factory
	{
	public:
		magma_engine::Component* createComponent(magma_engine::Entity* e);
	};

	extern "C" SUXALOTE_API void setUpGameFactories();
}

