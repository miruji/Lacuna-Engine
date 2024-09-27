#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "../Engine/Lua/State.h"
#include "mi.h"

namespace LE
{
	struct LuaFuncParam
	{
		bool loadStatus = true;

		std::vector<mi>      v_types;

		std::vector<float>       v_float;   // f
		std::vector<bool>        v_bool;    // b
		std::vector<std::string> v_string;  // s

		LuaFuncParam(lua_State* l, std::string vars);

		float get_f(mi num);
		bool get_b(mi num);
		std::string get_s(mi num);
	};
}
#define luaFuncParam(l, vars) \
	LuaFuncParam p(l, vars); \
	if (!p.loadStatus) return -1;