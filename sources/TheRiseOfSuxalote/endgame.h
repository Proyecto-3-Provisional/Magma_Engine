#pragma once

#include <EC/entity.h>

namespace magma_engine {
	class SceneManager;
	class Scene;
	class SceneLoader;
}

namespace magma_game
{

	class Endgame : public magma_engine::Component
	{
	public:
		Endgame();
		virtual ~Endgame();

		virtual bool initComponent(std::map<std::string, std::string> args);
		virtual bool start();
		void update(float deltaTime);

		void winOrLose(bool victory);

	private:

		std::string victoryRoute;
		std::string loseRoute;
	};
}
