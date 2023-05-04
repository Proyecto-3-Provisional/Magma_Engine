#include <EC/scene_manager.h>
#include <EC/scene.h>
#include <Lua/scene_loader.h>

namespace magma_engine
{
	SceneManager::SceneManager()
	{
		//Scene* escenaVacia = new Scene();
		//pushScene(escenaVacia);
	}

	SceneManager::~SceneManager()
	{
		while (!scenes.empty())
			popScene();
		deleteScenes();
	}

	void SceneManager::popScene()
	{
		if (!scenes.empty()) {
			scenesToDelete.push(scenes.top());
			scenes.pop();
		}
	}

	void SceneManager::pushScene(Scene* newScene)
	{
		Singleton<SceneLoader>::instance()->delScene();
		scenes.push(newScene);
	}

	void SceneManager::changeScene(Scene* newScene)
	{
		popScene();
		pushScene(newScene);
	}

	Scene* SceneManager::currentScene()
	{
		return scenes.top();
	}

	void SceneManager::update(float deltaTime)
	{
		if (!scenes.empty())
			scenes.top()->update(deltaTime);
		deleteScenes();
	}

	void SceneManager::deleteScenes()
	{
		while (!scenesToDelete.empty())
		{
			delete scenesToDelete.top();
			scenesToDelete.pop();
		}
	}
}
