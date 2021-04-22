#pragma once
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace dae
{
	int addNPC(lua_State* pLuaState);
	int removeNPC(lua_State* pLuaState);
	int dump(lua_State*);
	int setHealth(lua_State* pLuaState);
}