#pragma once

namespace magma_engine
{
	class EntityManager;

	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

		bool loadScene();
	};
}



