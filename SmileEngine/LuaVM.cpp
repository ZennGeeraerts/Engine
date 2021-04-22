#include "SmileEnginePCH.h"
#include "LuaVM.h"

dae::LuaVM::LuaVM()
	: m_pLuaState{ luaL_newstate() }
{
	luaL_openlibs(m_pLuaState);
}

dae::LuaVM::~LuaVM()
{
	lua_close(m_pLuaState);
}

void dae::LuaVM::RegisterFunction(const std::string& functionName, int function(lua_State*))
{
	lua_register(m_pLuaState, functionName.c_str(), function);
}

void dae::LuaVM::ExecuteString(const std::string& command, const std::string& value)
{
	int result = luaL_dostring(m_pLuaState, command.c_str());

	if (!CheckError(result))
	{
		lua_getglobal(m_pLuaState, value.c_str());
		if (lua_isnumber(m_pLuaState, -1))
		{ 
			float number{ float(lua_tonumber(m_pLuaState, -1)) };
			std::cout << number << std::endl;
		}
	}
}

void dae::LuaVM::ExecuteFile(const std::string& filePath)
{
	int result = luaL_dofile(m_pLuaState, filePath.c_str());
	CheckError(result);
}

bool dae::LuaVM::CheckError(int result)
{
	if (result != LUA_OK)
	{
		std::string errorMessage{ lua_tostring(m_pLuaState, -1) };
		std::cout << errorMessage << std::endl;
		return true;
	}

	return false;
}