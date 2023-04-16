#include "scene.h"
#include "entity_manager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
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
