#include "LuaParam.h"

LE::LuaFuncParam::LuaFuncParam(lua_State* l, std::string vars)
{
    mi varsLength = vars.length();
    if (lua_gettop(l) < varsLength)
    {
        loadStatus = false;
        return;
    }

    v_types.reserve(varsLength);
    v_float.reserve(varsLength);
    v_bool.reserve(varsLength);
    v_string.reserve(varsLength);
    varsLength = varsLength + 2;

    for (int i = 2; i < varsLength; i++)
    {
        char varType = vars[i - 2];
        int type = lua_type(l, i);

        switch (varType)
        {
        case 'f':
            if (type == LUA_TNUMBER)
            {
                v_float.emplace_back(lua_tonumber(l, i));
                v_types.emplace_back(v_float.size() - 1);
            }
            else if (type == LUA_TBOOLEAN)
            {
                v_float.emplace_back(lua_toboolean(l, i));
                v_types.emplace_back(v_float.size() - 1);
            }
            else if (type == LUA_TSTRING)
            {
                v_float.emplace_back(atof(lua_tostring(l, i)));
                v_types.emplace_back(v_float.size() - 1);
            }
            break;

        case 'b':
            if (type == LUA_TNUMBER)
            {
                v_bool.emplace_back(lua_tonumber(l, i) != 0);
                v_types.emplace_back(v_bool.size() - 1);
            }
            else if (type == LUA_TBOOLEAN)
            {
                v_bool.emplace_back(lua_toboolean(l, i));
                v_types.emplace_back(v_bool.size() - 1);
            }
            else if (type == LUA_TSTRING)
            {
                v_bool.emplace_back(atoi(lua_tostring(l, i)) != 0);
                v_types.emplace_back(v_bool.size() - 1);
            }
            break;

        case 's':
            if (type == LUA_TNUMBER)
            {
                v_string.emplace_back(std::to_string(lua_tonumber(l, i)));
                v_types.emplace_back(v_string.size() - 1);
            }
            else if (type == LUA_TBOOLEAN)
            {
                v_string.emplace_back(std::to_string(lua_toboolean(l, i)));
                v_types.emplace_back(v_string.size() - 1);
            }
            else if (type == LUA_TSTRING)
            {
                v_string.emplace_back(lua_tostring(l, i));
                v_types.emplace_back(v_string.size() - 1);
            }
            break;

        default:
            break;
        }
    }
}
float LE::LuaFuncParam::get_f(mi num)
{
	return v_float[v_types[num]];
}
bool LE::LuaFuncParam::get_b(mi num)
{
	return v_bool[v_types[num]];
}
std::string LE::LuaFuncParam::get_s(mi num)
{
	return v_string[v_types[num]];
}