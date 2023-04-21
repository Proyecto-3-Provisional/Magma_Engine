#include "lua_state_manager.h"

#include <lua.hpp>
#include "LuaBridge/LuaBridge.h"

LuaStateManager::LuaStateManager(): L(luaL_newstate()) {
    luaL_openlibs(L);
}

LuaStateManager::~LuaStateManager()
{
	lua_close(L);
}

lua_State* LuaStateManager::getLuaState() const
{
	return L;
}
