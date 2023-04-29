#pragma once

#include <singleton.h>
#include <string>
#include <map>

class lua_State;

/* > contiene entidades */
#define SceneMap std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>

/* > contiene componentes */
#define EntityMap std::map<std::string, std::map<std::string, std::string>>

/* > contiene argumentos */
#define ComponentMap std::map<std::string, std::string>

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
		SceneMap* getMapFile();

	private:
		void popLStack();
		void delScene();
		size_t readComponent(lua_State* L, ComponentMap* argsM);
		size_t readEntity(lua_State* L, EntityMap* cmpsM);

		lua_State* L = nullptr;
		SceneMap* lastLoadedScene = nullptr;
	};
}