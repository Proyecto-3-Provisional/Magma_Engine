#pragma once

#include <Lua/scene_loader.h>
#include <EC/entity_manager.h>

namespace magma_engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

		bool loadScene(SceneMap* map);

		bool isValid();

		std::vector<Entity*> getSceneEntities();

	private:

		bool valid;

		EntityManager* mngr;
	};
}
