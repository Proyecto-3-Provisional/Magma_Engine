#include "lua_main.h"

#include <lua.hpp>

#include <iostream>

#include "LuaBridge/LuaBridge.h"
#include <queue>

using namespace luabridge;

void printInfo() {
	std::cout << "INFO:\tMagma Scene Loader ~\n";
}

// Devuelve 0 si y solo si todo va bien
int extractEntityData(lua_State* L, std::string entityName, std::queue<std::map<std::string, std::string>>* entityCmps) {
	lua_getglobal(L, entityName.c_str()); // apilar tabla de datos de la entidad: mete 1
	if (lua_isnil(L, -1)) {	// comprobar que existen los datos: entidad declarada de verdad
		return 1; // ERROR
	}
	
	// Conjunto de componentes de la ent.
	std::map<std::string, std::string> cmps;

	for (size_t j = 0; j < NUM_P_CMPS; j++)
	{
		lua_pushstring(L, possibleCmps[j].c_str());	// apilar la petición: mete 1
		lua_gettable(L, -2);						// recoger valor: come 1; mete 1
		if (lua_istable(L, -1)) {	// comprobar si componente declarado, y que es tabla
			std::string cmpData = "";
			int k = 1;
			lua_pushinteger(L, k);		// apilar la petición: mete 1
			lua_gettable(L, -2);		// recoger valor: come 1; mete 1
			while (!lua_isnil(L, -1))
			{
				std::string auxstr = lua_tostring(L, -1);
				if (k != 1)
					cmpData += ",";
				cmpData += auxstr;
				lua_pop(L, 1);	// desapilar resultado: come 1; (t. entidades | t. entidad actual | t. componente actual)
				++k;
				lua_pushinteger(L, k);	// apilar la petición: mete 1
				lua_gettable(L, -2);	// recoger valor: come 1; mete 1
			}
			lua_pop(L, 1);	// desapilar resultado: come 1; (t. entidades | t. entidad actual | t. componente actual)
		
			// Registrar componente
			cmps.insert(std::make_pair(possibleCmps[j], cmpData));
			std::cout << "\n    * " << possibleCmps[j] << ":\t" << cmpData;
		}
		lua_pop(L, 1); // desapilar resultado: come 1; (t. entidades | t. entidad actual)
	}

	if (cmps.size() <= 0) {
		return 1; // ERROR
	}
	else {
		// Registrar entidad con sus componentes
		entityCmps->push(cmps);
	}

	return 0;
}

int luaMain(std::string filename) {
	// cola de entidades a buscar por el fichero
	std::queue<std::string> entityNames;
	// cola de mapas de comps. (nombre, args.)
	std::queue<std::map<std::string, std::string>> entityCmps;

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

	lua_getglobal(L, "entities"); // apilar lista de entidades: mete 1

	if (lua_istable(L, -1)) {
		int i = 1;					// índice para recorrer lista de entidades de escena
		lua_pushinteger(L, i);		// apilar la petición: mete 1
		lua_gettable(L, -2);		// recoger valor: come 1; mete 1
		while (!lua_isnil(L, -1)) {	// comprobación de fin de lista de entidades
			if (lua_isstring(L, -1)) {	// comprobar si es lo esperado, y actuar
				std::string entityName = lua_tostring(L, -1); // recoger nombre en C++
				entityNames.push(entityName);
			}
			lua_pop(L, 1);	// desapilar resultado: come 1; (tabla en la cima)
			++i;
			lua_pushinteger(L, i);	// apilar la petición: mete 1
			lua_gettable(L, -2);	// recoger valor: come 1; mete 1
		}
		lua_pop(L, 1);	// desapilar resultado: come 1; (tabla en la cima)

		int errAcc = 0; // número de entidades que no se pudieron interpretar
		std::cout << "SceneLoader:\t" << entityNames.size() << " entities declared in scene" << "\n";
		while (!entityNames.empty()) {	// recorrer cola de entidades a buscar
			// Construir serie de componentes con sus parámetros, para cada entidad
			std::cout << " " << entityNames.front();
			if (extractEntityData(L, entityNames.front(), &entityCmps))
			{
				std::cout << "\t- [FAILED]";
				++errAcc;
			}
			std::cout << "\n";
			entityNames.pop(); // siguiente entidad...
		}
		std::cout << "SceneLoader:\t" << errAcc << " entities could not be parsed" << "\n";
	}

	// Desapilar todo Lua
	while (lua_gettop(L) > 0)
	{
		lua_pop(L, 1);
	}

	// Cierre de Lua
	lua_close(L);
	L = nullptr;

	return 0;
}
