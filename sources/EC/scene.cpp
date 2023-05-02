#include <EC/scene.h>
#include <EC/entity_manager.h>
#include <EC/factory_manager.h>

#include <Render/render_manager.h>

namespace magma_engine
{
	Scene::Scene() : valid(false)
	{
		if (Singleton<FactoryManager>::instance())
			valid = true;
		mngr = new ec::EntityManager();
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

		if (sceneMap == nullptr)
			return false;

		Singleton<magma_engine::RenderManager>::instance()->
			createCam(nullptr, { 0, 1000, 0 });
		Singleton<magma_engine::RenderManager>::instance()->
			setCamLookAt({ 0, -1000, 0 });
		Singleton<magma_engine::RenderManager>::instance()->
			setBgColor(0.8f, 0.8f, 0.7f);
		Singleton<magma_engine::RenderManager>::instance()->
			objectShowMode(0);

		for (auto itEntity = sceneMap->begin();
			itEntity != sceneMap->end() && noErrors;
			itEntity++)
		{
			ec::Entity* e = mngr->addEntity();

			for (auto itComponent = itEntity->second.begin();
				itComponent != itEntity->second.end() && noErrors;
				itComponent++)
			{
				ec::Component* c = Singleton<FactoryManager>::instance()->
					findAndCreate(itComponent->first, e);
				if (c != nullptr) {
					bool successfulInit = c->initComponent(itComponent->second);
					if (!successfulInit) { // borrar entidad
						delete c;
						c = nullptr;
					}
					noErrors = successfulInit && noErrors;
				}
			}
		}

		if (!noErrors)
			return false;
		
		for (ec::Entity* e : mngr->getEntities())
		{
			if (!noErrors)
				break;
			for (magma_engine::ec::Component* cmp : e->getAllCmps())
			{
				if (!noErrors)
					break;

				bool successfulStart = cmp->start();
				if (!successfulStart) { 
					// borrar entidad ?
				}
				noErrors = successfulStart && noErrors;
			}
		}

		return noErrors;
	}

	bool Scene::isValid()
	{
		return valid;
	}
}
