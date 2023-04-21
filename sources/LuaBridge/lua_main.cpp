#include "lua_main.h"

#include <lua.hpp>

#include <iostream>

#include "LuaBridge/LuaBridge.h"
#include "lua_state_manager.h"


using namespace luabridge;

void foo();

int luaMain(std::string filename){
	
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);


	//getGlobalNamespace(L) //abrimos espacio de nombres
	//	.beginNamespace("Test")
	//	/*.addFunction("foo", foo)*/
	//.endNamespace() //cerramos globalNamespace
	;

	int r = luaL_dofile(L, filename.c_str());

	if (r != LUA_OK) {
		std::cout << "Error al abrir fichero Lua";
		lua_close(L);
		return -1;
	}

	//LuaRef s = getGlobal(L, "player");

	//if (!s.isNumber()) {
	//	std::cout << s.tostring() << '\n'; //tostring quita " "" "
	//}
	//

	//LuaRef xd = getGlobal(L, "entities");

	/*if (xd.isTable()) {
		std::string straux = xd[1];
		LuaRef xd2 = getGlobal(L, straux.c_str());

		if (xd2.isTable()) {
			std::string straux2 = xd2["nombre"];

			if (xd2["nombre"].isString())
				std::cout << xd2["nombre"].tostring() << '\n';
		}
	}*/
	/*while (lua_gettop(L) > 0)
		lua_pop(L, 1);
		*/

	lua_close(L);
	
	// 
	//error porque esta intentado hacer la recoleccion de basura posterior
	//delete stateManager; stateManager = nullptr;

	return 0;
}

void foo() {
	std::cout << "AQUIIII AQUI AQUI AUIIIIII AAAAAAAAA\n";
}



//EJEMPLO LUABRIDGE, PARA LLAMAR A FOO ESCRIBIRIAS EN EL ARCHIVO LUA Test:foo()

