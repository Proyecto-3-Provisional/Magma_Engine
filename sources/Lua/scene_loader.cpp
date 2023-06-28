#include "scene_loader.h"
#include <lua.hpp>
#include <LuaBridge/LuaBridge.h> // LuaBridge/LuaBridge.h
#include <iostream>

using namespace luabridge;

namespace magma_engine
{
	// vvv Funciones a exponer para Lua vvv //
	void printInfo() {
		std::cout << "INFO:\tMagma Scene Loader ~\n";
	}
	// ^^^ Funciones a exponer para Lua ^^^ //

	SceneLoader::SceneLoader()
	{
		// Apertura de Lua
		L = luaL_newstate();
		luaL_openlibs(L);

		// Espacio de nombres; registrar funciones para Lua
		getGlobalNamespace(L).beginNamespace("SceneLoader")
			.addFunction("printInfo", printInfo)
			.endNamespace();
	}

	SceneLoader::~SceneLoader()
	{
		// Borrar escena si existe
		while (!loadedScenes.empty()) {
			auto iter = loadedScenes.begin();
			delete (*iter).second; (*iter).second = nullptr;
			loadedScenes.erase(iter);
		}

		//delScene();

		// Cierre de Lua
		lua_close(L);
		L = nullptr;
	}

	void SceneLoader::popLStack() {
		// Desapilar todo Lua
		while (lua_gettop(L) > 0) {
			lua_pop(L, 1);
		}
	}

	// Devuelve el tamaño del mapa de argumentos del componente
	size_t SceneLoader::readComponent(lua_State* L, ComponentMap* argsM)
	{
		std::string argumentName = "";
		std::string argumentValue = "";
		//+1
		lua_pushnil(L);						
		// ¡ahora se pasa a recorrer la tabla del componente!
		//-1;+2/+0
		while (lua_next(L, -2) != 0) {		
			// valor: -1; clave: -2

			if (lua_isstring(L, -2) && lua_isstring(L, -1)) {
				argumentName = lua_tostring(L, -2);
				argumentValue = lua_tostring(L, -1);
				std::cout << "    " << argumentName << ": " << argumentValue << "\n";
				// añadir argumento
				argsM->insert(std::make_pair(argumentName, argumentValue));
			}
			//-1
			lua_pop(L, 1);					
		}
		// clave desaparece

		std::cout << "    . " << argsM->size() << "\n";
		return argsM->size();
	}

	// Devuelve el tamaño del mapa de componentes de la entidad
	size_t SceneLoader::readEntity(lua_State* L, EntityMap* cmpsM)
	{
		std::string componentName = "";
		//+1
		lua_pushnil(L);						
		// ¡ahora se pasa a recorrer la tabla de la entidad!
		//-1;+2/+0
		while (lua_next(L, -2) != 0) {		
			// tras lua_next: valor en -1; clave en -2
			componentName = lua_tostring(L, -2);
			std::cout << "  " << componentName << "\n";

			if (lua_istable(L, -1))
			{
				std::map<std::string, std::string> auxM;
				if (readComponent(L, &auxM) >= 0)
				{
					// añadir componente
					cmpsM->insert(std::make_pair(componentName, auxM));
				}
			}
			//-1
			lua_pop(L, 1);					
		}
		// lua_next quita clave final

		std::cout << "  - " << cmpsM->size() << "\n";
		return cmpsM->size();
	}

	// Devuelve 0 solo si todo fue bien
	int SceneLoader::loadScene(std::string filename) {
		// Mapa de Entidades -> Mapa de Componentes -> Argumentos
		SceneMap* sceneMap;

		// Lectura y evaluación del fichero
		std::string file = "assets/scenes/" + filename + ".magmascene";
		int r = luaL_dofile(L, filename.c_str());
		if (r != LUA_OK) {
			std::cout << "Error loading scene: " << file << "\n";
			// ERROR al leer el fichero
			return -1; 
		}

		// Ir reservando memoria...
		sceneMap = new SceneMap;

		int nEnts = 0;
		//+1 // apilar lista de entidades
		lua_getglobal(L, "entities");		
		if (lua_istable(L, -1)) {
			std::string entityName = "";

			/* https://www.lua.org/manual/5.4/manual.html#lua_next */
			//+1 // apilar nada
			lua_pushnil(L);					
			//-1;+2/+0 // siguiente elemento de la tabla
			while (lua_next(L, -2) != 0) {	
				// CIMA -> valor -> clave -> ...
				entityName = lua_tostring(L, -2);
				std::cout << entityName << "\n";

				if (lua_istable(L, -1))
				{
					std::map<std::string, std::map<std::string, std::string>> auxM;
					if (readEntity(L, &auxM) > 0)
					{
						// registrar entidad
						sceneMap->insert(std::make_pair(entityName, auxM));
						++nEnts;
					}
				}
				// -1 // quitar valor, mantener clave para lua_next
				lua_pop(L, 1);				
			}
			// ¡ lua_next quita la clave final al terminar el bucle !

			std::cout << "* " << nEnts << "\n";
		}
		//+1 // desapilar lista de entidades
		lua_pop(L, 1);						

		if (nEnts <= 0) {
			// Deshacer lo hecho...
			delete sceneMap;
			sceneMap = nullptr;
			return -1;
		}
		else {
			loadedScenes.insert(std::make_pair(filename, sceneMap));
			return 0;
		}
	}

	// Devuelve el fichero de la escena con todas las entidades y componentes
	SceneMap* SceneLoader::getMapFile(std::string filename)
	{
		return loadedScenes[filename];
	}
}