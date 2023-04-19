#include "lua_main.h"

#include <lua.hpp>

#include <iostream>

int luaMain(){
	lua_State* L = luaL_newstate();
	int r = luaL_dofile(L, "luatest.lua");
	std::string name;

	if (r == LUA_OK) { //luabridge nos ayudara a evitar el uso de control de niveles en la pila(-1, -2...)
		lua_getglobal(L, "player");
		if (lua_istable(L, -1)) {
			lua_pushstring(L, "name");
			lua_gettable(L, -2);
			name = lua_tostring(L, -1);

			lua_pop(L, -1);

			std::cout << name << '\n';
		}
	}
	else {
		std::cout << "LUA WARNING, SCRIPT INCORRECTO O NO ENCONTRADO";
	}

	return 0;
}
