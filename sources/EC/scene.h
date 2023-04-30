#pragma once

#include <Lua/scene_loader.h>
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

	private:
		bool valid;
	};
}
