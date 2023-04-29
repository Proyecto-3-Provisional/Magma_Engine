#include <EC/scene.h>
#include <EC/entity_manager.h>
#include <EC/factory_manager.h>
#include <Lua/scene_loader.h>

namespace magma_engine
{
	Scene::Scene() : valid(false)
	{
		if (Singleton<ec::EntityManager>::instance() &&
			Singleton<FactoryManager>::instance()
		)
			valid = true;
	}

	Scene::~Scene()
	{
	}

	void Scene::update(float deltaTime)
	{
		ec::EntityManager::instance()->update(deltaTime);
		ec::EntityManager::instance()->refresh();
	}

	bool Scene::loadScene(SceneMap* map)
	{
		bool noErrors = true;

		if (map != nullptr)
		{
			for (auto itEntity = map->begin(); itEntity != map->end(); itEntity++)
			{
				ec::Entity* e = ec::EntityManager::instance()->addEntity();

				for (auto itComponent = itEntity->second.begin(); itComponent != itEntity->second.end(); itComponent++)
				{
					ec::Component* c = Singleton<FactoryManager>::instance()->findAndCreate(itComponent->first, e);
					noErrors = noErrors && c->initComponent(itComponent->second);
				}
			}
		}
		else return false;
		
		return noErrors;
	}

	bool Scene::isValid()
	{
		return valid;
	}
}

