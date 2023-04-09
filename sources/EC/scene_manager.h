#pragma once

#include "../singleton.h"
#include <stack>
#include <string>

class Scene;

class SceneManager : public Singleton<SceneManager> {

public:
	~SceneManager();

	void popScene();

	void pushScene(Scene* newScene);

	void changeScene(Scene* newScene);

	Scene* currentScene();

	void update(float deltaTime);
private:
	SceneManager();

	void deleteScenes();

	std::stack<Scene*> scenes;
	std::stack<Scene*> scenesToDelete;
};