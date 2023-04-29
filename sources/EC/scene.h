#pragma once
#include <string>

namespace magma_engine
{
	class EntityManager;
	class SceneLoader;

	class Scene
	{
		public:
			Scene();
			~Scene();

			void update(float deltaTime);

			bool loadScene(std::string fileName);
	};
}



