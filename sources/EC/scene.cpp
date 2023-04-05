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
}

bool Scene::loadScene()
{
	return false;
}
