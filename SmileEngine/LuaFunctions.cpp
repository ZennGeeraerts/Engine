#include "SmileEnginePCH.h"
#include "LuaFunctions.h"

#include "NPCManager.h"


int dae::addNPC(lua_State* pLuaState)
{
	std::string name{ lua_tostring(pLuaState, 1) };
	NPCManager::GetInstance().AddNPC(name);
	return 1;
}

int dae::removeNPC(lua_State* pLuaState)
{
	std::string name{ lua_tostring(pLuaState, 1) };
	NPCManager::GetInstance().RemoveNPC(name);
	return 1;
}

int dae::dump(lua_State*)
{
	NPCManager::GetInstance().Dump();
	return 1;
}

int dae::setHealth(lua_State* pLuaState)
{
	std::string name{ lua_tostring(pLuaState, 1) };
	int health{ static_cast<int>(lua_tonumber(pLuaState, 2)) };
	NPCManager::GetInstance().SetHealth(name, health);
	return 1;
}