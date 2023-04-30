#include <EC/scene.h>
#include <EC/entity_manager.h>
#include <EC/factory_manager.h>

#include <Render/render_manager.h>

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

		Singleton<magma_engine::RenderManager>::instance()->createCam(nullptr, { 0, 1000, 0 });
		Singleton<magma_engine::RenderManager>::instance()->setCamLookAt({ 0, -1000, 0 });
		Singleton<magma_engine::RenderManager>::instance()->setBgColor(0.8f, 0.8f, 0.7f);
		Singleton<magma_engine::RenderManager>::instance()->objectShowMode(0);

		if (map != nullptr)
		{
			for (auto itEntity = map->begin(); itEntity != map->end(); itEntity++)
			{
				ec::Entity* e = ec::EntityManager::instance()->addEntity();

				for (auto itComponent = itEntity->second.begin(); itComponent != itEntity->second.end(); itComponent++)
				{
					ec::Component* c = Singleton<FactoryManager>::instance()->findAndCreate(itComponent->first, e);
					noErrors = c->initComponent(itComponent->second) && noErrors;

					// Si el componente falla, hay que borrarlo

				}
			}
		}
		else return false;
		
		for (ec::Entity* e : ec::EntityManager::instance()->getEntities())
		{
			for (int i = 0; i < e->getAllCmps().size(); i++)
			{
				e->getAllCmps()[i]->start();
			}
		}

		
		return noErrors;
	}

	bool Scene::isValid()
	{
		return valid;
	}
}

