#include <EC/scene.h>
#include <EC/entity_manager.h>
#include <EC/factory_manager.h>
#include <EC/scene_manager.h>

#include <Render/render_manager.h>

#include <Render/ui_manager.h>

namespace magma_engine
{
	Scene::Scene() : valid(false)
	{
		if (Singleton<FactoryManager>::instance())
			valid = true;
		mngr = new EntityManager();
	}

	Scene::~Scene()
	{
		delete mngr; mngr = nullptr;
	}

	void Scene::update(float deltaTime)
	{
		mngr->update(deltaTime);
		mngr->refresh();
	}

	bool Scene::loadScene(SceneMap* sceneMap)
	{
		bool noErrors = true;

		if (sceneMap == nullptr) {
			Singleton<magma_engine::SceneManager>::instance()->setSceneFailed();
			return false;
		}


		for (auto itEntity = sceneMap->begin();
			itEntity != sceneMap->end() && noErrors;
			itEntity++)
		{
			Entity* e = mngr->addEntity();

			for (auto itComponent = itEntity->second.begin();
				itComponent != itEntity->second.end() && noErrors;
				itComponent++)
			{
				Component* c = Singleton<FactoryManager>::instance()->
					findAndCreate(itComponent->first, e);
				if (c != nullptr) {
					bool successfulInit = c->initComponent(itComponent->second);

					noErrors = successfulInit && noErrors;
				}
			}
		}

		if (!noErrors) {
			Singleton<magma_engine::SceneManager>::instance()->setSceneFailed();
			return false;
		}
		
		for (Entity* e : mngr->getEntities())
		{
			if (!noErrors)
				break;
			for (Component* cmp : e->getAllCmps())
			{
				if (!noErrors)
					break;

				bool successfulStart = cmp->start();
				if (!successfulStart) { 

				}
				noErrors = successfulStart && noErrors;
			}
		}

		if (!noErrors) {
			Singleton<magma_engine::SceneManager>::instance()->setSceneFailed();
			return false;
		}

		return true;
	}

	bool Scene::isValid()
	{
		return valid;
	}

	std::vector<Entity*> Scene::getSceneEntities() {
		return mngr->getEntities();
	}
}
