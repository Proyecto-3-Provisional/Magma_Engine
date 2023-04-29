#include <EC/scene.h>
#include <EC/entity_manager.h>
#include <Lua/scene_loader.h>
#include <EC/factory_manager.h>

namespace magma_engine
{
	Scene::Scene()
	{
		Singleton<SceneLoader>::init();

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

	bool Scene::loadScene(std::string fileName)
	{
		Singleton<SceneLoader>::instance()->loadScene(fileName);

		SceneMap* file = Singleton<SceneLoader>::instance()->getMapFile();

		if (file != nullptr)
		{

			for (auto itEntity = file->begin(); itEntity != file->end(); itEntity++)
			{
				ec::Entity* e = ec::EntityManager::instance()->addEntity();

				for (auto itComponent = itEntity->second.begin(); itComponent != itEntity->second.end(); itComponent++)
				{
					for (auto itArgs = itComponent->second.begin(); itArgs != itComponent->second.end(); itArgs++)
					{
						ec::Component* c = Singleton<FactoryManager>::instance()->findAndCreate(itComponent->first, e);
						//c->initComponent(itArgs);
						
					}
				}
			}
		}
		


		// Pasar LUA a scene bien
		Singleton<ec::EntityManager>::init();
		return false;
	}
}

