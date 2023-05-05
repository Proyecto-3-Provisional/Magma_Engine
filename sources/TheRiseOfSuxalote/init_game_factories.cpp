#include <EC/factory_manager.h>
#include <EC/entity.h>

#include <TheRiseOfSuxalote/init_game_factories.h>
#include <TheRiseOfSuxalote/enemy_controller.h>
#include <TheRiseOfSuxalote/player_controller.h>
#include <TheRiseOfSuxalote/size_temp.h>
#include <TheRiseOfSuxalote/progress_bar.h>
#include <TheRiseOfSuxalote/timer.h>
#include <TheRiseOfSuxalote/power_up.h>
#include <TheRiseOfSuxalote/endgame.h>

namespace magma_game
{
	magma_engine::Component* ProgressBarFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<Progress_Bar>();
	}

	magma_engine::Component* TimerFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<Timer>();
	}

	magma_engine::Component* PlayerControllerFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<PlayerController>();
	}

	magma_engine::Component* EnemyControllerFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<EnemyController>();
	}

	magma_engine::Component* SizeTempFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<Size_Temp>();
	}

	magma_engine::Component* PowerUpFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<PowerUpComponent>();
	}

	magma_engine::Component* EndgameFactory::createComponent(magma_engine::Entity* e)
	{
		return e->addComponent<Endgame>();
	}

	void setUpGameFactories()
	{
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("PlayerController", new PlayerControllerFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("EnemyController", new EnemyControllerFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("ProgressBar", new ProgressBarFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("Timer", new TimerFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("Size_Temp", new SizeTempFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("Endgame", new EndgameFactory());
		Singleton<magma_engine::FactoryManager>::instance()->addFactory("PowerUpComponent", new PowerUpFactory());
	}
}

