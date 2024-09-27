#pragma once
#include "LuaMacro.h"
#include "State.h"

#include <iostream>
#include <vector>

#include <optional>
#include <unordered_map>

namespace LE
{
	std::optional<float> luaToFloat(lua_State* l, int index);

	std::vector<std::string> luaParts(const std::string& globalName);
	void luaTable(lua_State* l, const std::string& tableName, std::string childTable = "");
	void luaFunction(lua_State* l, const std::string& globalName, const std::string& functionName, lua_CFunction func);
}