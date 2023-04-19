#include <EC/scene.h>
#include <EC/entity_manager.h>

Scene::Scene()
{
	Singleton<ec::EntityManager>::init();
}

Scene::~Scene()
{
	Singleton<ec::EntityManager>::release();
}

void Scene::update(float deltaTime)
{
	ec::EntityManager::instance()->update(deltaTime);
	ec::EntityManager::instance()->refresh();
}

bool Scene::loadScene()
{
	return false;
}
