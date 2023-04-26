#include "lua_main.h"

#include <lua.hpp>
#include <iostream>

#include "LuaBridge/LuaBridge.h"

using namespace luabridge;

void printInfo() {
	std::cout << "INFO:\tMagma Scene Loader ~\n";
}

// Devuelve el tamaño del mapa de argumentos del componente
int readComponent(lua_State* L,	std::map<std::string, std::string>* argsM)
{
	std::string argumentName = "";
	std::string argumentValue = "";

	lua_pushnil(L);						//+1
	// ¡ahora se pasa a recorrer la tabla del componente!
	while (lua_next(L, -2) != 0) {		//-1;+2/+0
		// valor: -1; clave: -2

		if (lua_isstring(L, -2) && lua_isstring(L, -1)) {
			argumentName = lua_tostring(L, -2);
			argumentValue = lua_tostring(L, -1);
			std::cout << "    " << argumentName << ": " << argumentValue << "\n";
			// añadir argumento
			argsM->insert(std::make_pair(argumentName, argumentValue));
		}

		lua_pop(L, 1);					//-1
	}
	// clave desaparece

	std::cout << "    . " << argsM->size() << "\n";
	return argsM->size();
}

// Devuelve el tamaño del mapa de componentes de la entidad
int readEntity(lua_State* L, std::map<std::string, std::map<std::string, std::string>>* cmpsM)
{
	std::string componentName = "";

	lua_pushnil(L);						//+1
	// ¡ahora se pasa a recorrer la tabla de la entidad!
	while (lua_next(L, -2) != 0) {		//-1;+2/+0
		// tras lua_next: valor en -1; clave en -2
		componentName = lua_tostring(L, -2);
		std::cout << "  " << componentName << "\n";

		if (lua_istable(L, -1))
		{
			std::map<std::string, std::string> auxM;
			if (readComponent(L, &auxM) > 0)
			{
				// añadir componente
				cmpsM->insert(std::make_pair(componentName, auxM));
			}
		}

		lua_pop(L, 1);					//-1
	}
	// lua_next quita clave final
	
	std::cout << "  - " << cmpsM->size() << "\n";
	return cmpsM->size();
}

// Devuelve 0 solo si todo fue bien
int luaMain(std::string filename) {
	// Mapa de Entidades -> Mapa de Componentes -> Argumentos
	std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>* sceneMap;
	sceneMap = new std::map<std::string, std::map<std::string, std::map<std::string, std::string>>>;

	// Apertura de Lua
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//espacio de nombres
	getGlobalNamespace(L).beginNamespace("SceneLoader")
		.addFunction("printInfo", printInfo)
		.endNamespace();

	// Lectura y evaluación del fichero
	int r = luaL_dofile(L, filename.c_str());
	if (r != LUA_OK) {
		std::cout << "Error loading scene: " << filename << "\n";
		lua_close(L);
		return -1; // ERROR al leer el fichero
	}

	int nEnts = 0;
	lua_getglobal(L, "entities");		//+1 // apilar lista de entidades
	if (lua_istable(L, -1)) {
		std::string entityName = "";

		/* https://www.lua.org/manual/5.4/manual.html#lua_next */
		lua_pushnil(L);					//+1 // apilar nada
		while (lua_next(L, -2) != 0) {	//-1;+2/+0 // siguiente elemento de la tabla
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

			lua_pop(L, 1);				// -1 // quitar valor, mantener clave para lua_next
		}
		// ¡ lua_next quita la clave final al terminar el bucle !

		std::cout << "* " << nEnts << "\n";
	}

	// Desapilar todo Lua
	while (lua_gettop(L) > 0)
	{
		lua_pop(L, 1);
	}

	// Cierre de Lua
	lua_close(L);
	L = nullptr;

	// Borrar mapa
	delete sceneMap;
	sceneMap = nullptr;

	if (nEnts <= 0)
	{
		return -1;
	}
	return 0;
}