#pragma once

#include <singleton.h>

#include <stack>
#include <string>

namespace magma_engine
{
	class Scene;

	class SceneManager : public Singleton<SceneManager> {

	public:
		SceneManager();
		~SceneManager();

		void popScene();

		void pushScene(Scene* newScene);

		void changeScene(Scene* newScene);

		Scene* currentScene();

		void update(float deltaTime);
	private:


		void deleteScenes();

		std::stack<Scene*> scenes;
		std::stack<Scene*> scenesToDelete;
	};
}

