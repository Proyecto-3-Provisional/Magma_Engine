#pragma once

#ifdef MAGMAENGINE_EXPORTS
#define MAGMAENGINE_API __declspec(dllexport)
#else
#define MAGMAENGINE_API __declspec(dllimport)
#endif

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
	class MAGMAENGINE_API SceneLoader : public Singleton<SceneLoader>
	{
		// Permiso para construir
		friend Singleton<SceneLoader>;

	public:
		SceneLoader();
		~SceneLoader();
		int loadScene(std::string filename);
		SceneMap* getMapFile();

		void delScene();

	private:
		void popLStack();
		size_t readComponent(lua_State* L, ComponentMap* argsM);
		size_t readEntity(lua_State* L, EntityMap* cmpsM);

		lua_State* L = nullptr;
		SceneMap* lastLoadedScene = nullptr;
	};
}