#pragma once
#include <string>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace dae
{
	class LuaVM final
	{
	public:
		LuaVM();
		~LuaVM();

		void RegisterFunction(const std::string& functionName, int function(lua_State*));
		void ExecuteString(const std::string& command, const std::string& value);
		void ExecuteFile(const std::string& filePath);

	private:
		bool CheckError(int result);

		lua_State* m_pLuaState;
	};
}
