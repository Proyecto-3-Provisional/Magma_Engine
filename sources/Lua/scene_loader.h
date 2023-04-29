#pragma once

#include <singleton.h>
#include <string>
#include <map>

class lua_State;

#define SceneMap std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>
	/* > contiene entidades */

#define EntityMap std::map<std::string, std::map<std::string, std::string>>
	/* > contiene componentes */

#define ComponentMap std::map<std::string, std::string>
	/* > contiene argumentos */

namespace magma_engine
{
	class SceneLoader : public Singleton<SceneLoader>
	{
		// Permiso para construir
		friend Singleton<SceneLoader>;
	protected:
		explicit SceneLoader();
	public:
		virtual ~SceneLoader();
		int loadScene(std::string filename);
	private:
		void popLStack();
		void delScene();
		size_t readComponent(lua_State* L, ComponentMap* argsM);
		size_t readEntity(lua_State* L, EntityMap* cmpsM);

		lua_State* L = nullptr;
		SceneMap* lastLoadedScene = nullptr;
	};
}