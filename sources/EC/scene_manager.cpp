#include <EC/scene_manager.h>
#include <EC/scene.h>
#include <EC/entity.h>
#include <Lua/scene_loader.h>
#include <Render/render_manager.h>

namespace magma_engine
{
	SceneManager::SceneManager() : sceneFailed(false)
	{

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
			if (!scenes.empty())
				for (auto* e : currentScene()->getSceneEntities()) {
					for (auto* c : e->getAllCmps())
						c->onEnable();
				}
		}
	}

	void SceneManager::pushScene(Scene* newScene)
	{
		if (!scenes.empty())
			for (auto* e : currentScene()->getSceneEntities()) {
				for (auto* c : e->getAllCmps())
					c->onDisable();
			}
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



	void SceneManager::setSceneFailed(std::string scene)
	{
		Singleton<magma_engine::RenderManager>::instance()->makeMessageBox("LUA", ("La escena " + scene + " no se ha podido cargar con exito").c_str());
		sceneFailed = true;
	}

	bool SceneManager::isSceneFailed() {
		return sceneFailed;
	}
}
