#include "scene_manager.h"
#include "scene.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
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
