#pragma once

//class lua_State;

//me parece que necesita estar aqui
#include <lua.hpp>

//clase para asegurar creacion y destruccion correcta de luaState
class LuaStateManager {
public:
    LuaStateManager();
    ~LuaStateManager();

    lua_State* getLuaState() const;

private:
    lua_State* L;
};