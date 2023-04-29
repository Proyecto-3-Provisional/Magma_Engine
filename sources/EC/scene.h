#pragma once

#include <map>
#include <string>

namespace magma_engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void update(float deltaTime);

		bool loadScene(std::map<std::string,
						std::map<std::string,
							std::map<std::string,
								std::string>>>* map);

		bool isValid();

	private:
		bool valid;
	};
}
