#include "LuaLoad.h"

// Helper function to convert a Lua value to a float
std::optional<float> LE::luaToFloat(lua_State* l, int index)
{
    if (lua_isnumber(l, index)) {
        return static_cast<float>(lua_tonumber(l, index));
    }
    return std::nullopt;
}
// parts
std::vector<std::string> LE::luaParts(const std::string& globalName)
{
    std::vector<std::string> globalNameParts;
    std::string buffer;

    for (const char c : globalName)
    {
        if (c == '.')
        {
            globalNameParts.emplace_back(buffer);
            buffer.clear();
        }
        else
            buffer += c;
    }

    globalNameParts.emplace_back(buffer);
    return globalNameParts;
}
// table
void LE::luaTable(lua_State* l, const std::string& tableName, std::string childTable)
{
    if (childTable == "")
    {
        // _G[tableName] = {}
        lua_newtable(l);
        lua_setglobal(l, tableName.c_str());
    }
    else
    {
        std::vector<std::string> globalNameParts = luaParts(tableName);
        lua_getglobal(l, globalNameParts[0].c_str());

        for (int i = 1; i < globalNameParts.size(); i++)
        {
            lua_pushstring(l, globalNameParts[i].c_str());
            lua_gettable(l, -2);
        }

        lua_newtable(l);
        lua_setfield(l, -2, childTable.c_str());

        lua_pop(l, static_cast<int>(globalNameParts.size() - 2));
    }
}
// func
void LE::luaFunction(lua_State* l, const std::string& globalName, const std::string& functionName, lua_CFunction func)
{
    std::vector<std::string> globalNameParts = luaParts(globalName);
    lua_getglobal(l, globalNameParts[0].c_str());

    for (auto part = std::next(globalNameParts.begin()); part != globalNameParts.end(); ++part)
        lua_getfield(l, -1, part->c_str());

    lua_pushcfunction(l, func);
    lua_setfield(l, -2, functionName.c_str());

    lua_pop(l, static_cast<int>(globalNameParts.size() - 2));
}