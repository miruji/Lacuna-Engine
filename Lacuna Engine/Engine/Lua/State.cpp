#include "State.h"
using namespace LE;

State::State()
{
	L = luaL_newstate();
	luaL_openlibs(L);
}
State::~State()
{
}
void State::del()
{
	lua_close(L);
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > GET
int State::loadFile(const char* fileName)
{
	int error = luaL_dofile(L, fileName);
	this->fileName = fileName;
	if (error)
	{
		printf("LE::State.cpp::State::LoadFile():: %s\n", lua_tostring(L, -1));
		lua_pop(L, lua_gettop(L));
		throw("LE::State.cpp::State::LoadFile():: Could not open file %s\n", fileName); // <<-- TO:DO double quotes

		return error;
	}
	else
		return 0;
}
int State::func(const char* name)
{
	lua_getglobal(L, name);
	int error = lua_pcall(L, 0, 0, 0);
	if (error)
	{
		printf("LE::State.cpp::Func():: Failed to call \"%s\" function\n", name);
		lua_pop(L, lua_gettop(L));
		throw("LE::State.cpp::Func():: Failed to call \"%s\" function\n", name);

		return error;
	}
	else
		return 0;
}
int State::num(const char* name)
{
	lua_getglobal(L, name);
	return lua_tointeger(L, lua_gettop(L));
}
std::string State::str(const char* name)
{
	lua_getglobal(L, name);

	if (lua_tostring(L, lua_gettop(L)))
		return lua_tostring(L, lua_gettop(L));
	else return "";
}
std::string State::getTableString(const char* tableName, const char* key)
{
    lua_getglobal(L, tableName);
    if (!lua_istable(L, -1)) {
        lua_pop(L, 1);
        throw std::runtime_error("table not found\n");
    }

    lua_pushstring(L, key);
    lua_gettable(L, -2);

    std::string result;
    if (lua_isstring(L, -1)) {
        result = lua_tostring(L, -1);
    }
    lua_pop(L, 2);  // remove table and value

    if (result.empty()) {
        throw std::runtime_error("key not found in table\n");
    }

    return result;
}

// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > SET
void State::jsonTable(const std::string& tableName, const std::string& Str)
{
	cJSON* json = cJSON_Parse(Str.c_str());
	lua_newtable(L);

	if (json == nullptr)
	{
		std::cerr << "Failed to parse JSON: " << cJSON_GetErrorPtr() << "\n";
		return;
	}

	lua_newtable(L);
	cJSON* item = json->child;

	while (item != nullptr)
	{
		const char* key = item->string;
		switch (item->type)
		{
			case cJSON_String:
			lua_pushstring(L, item->valuestring);
			break;
			case cJSON_Number:
			lua_pushnumber(L, item->valuedouble);
			break;
			case cJSON_True:
			lua_pushboolean(L, true);
			break;
			case cJSON_False:
			lua_pushboolean(L, false);
			break;
			case cJSON_Array:
			// рекурсивный вызов для обработки вложенного массива
			break;
			case cJSON_Object:
			// рекурсивный вызов для обработки вложенного объекта
			break;
			default:
			std::cerr << "Unexpected JSON type: " << item->type << std::endl;
			break;
		}
		lua_setfield(L, -2, key);
		item = item->next;
	}

	cJSON_Delete(json);
	// сохраняем созданную таблицу на стеке в глобальную переменную "Scene"
	lua_setglobal(L, tableName.c_str());
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// > OUTPUT
void State::printAll(int level)
{
	int index = lua_gettop(L);

	// проверяем, что таблица была передана
	if (!lua_istable(L, index))
	{
		std::cout << "not a table" << std::endl;
		return;
	}

	// создаем итератор для таблицы
	lua_pushnil(L);
	while (lua_next(L, index))
	{
		// выводим префикс для отступов
		for (int i = 0; i < level; i++)
			std::cout << "  ";

		// получаем значение элемента таблицы
		const char* key = lua_tostring(L, -2);
		std::cout << key << " = ";

		// если элемент - таблица, то рекурсивно выводим ее содержимое
		if (lua_istable(L, -1))
		{
			std::cout << "\n";
			printAll(level+1);
		}
		else
		{
			const char* value = lua_tostring(L, -1);
			std::cout << value << "\n";
		}

		// удаляем значение элемента таблицы
		lua_pop(L, 1);
	}
}
void State::save(const char* filename)
{
	int index = lua_gettop(L);

	std::ofstream file;
	file.open(filename);

	if (!file.is_open())
	{
		std::cout << "failed to open file" << std::endl;
		return;
	}

	if (!lua_istable(L, index))
	{
		std::cout << "not a table" << std::endl;
		return;
	}

	file << "{";
	lua_pushnil(L);
	while (lua_next(L, index))
	{
		if (lua_isstring(L, -2))
			file << "\n    " << lua_tostring(L, -2) << " = ";
		else
			file << "\n    [" << lua_tonumber(L, -2) << "] = ";

		if (lua_istable(L, -1))
			save(filename);
		else if (lua_isstring(L, -1))
			file << "\"" << lua_tostring(L, -1) << "\",";
		else if (lua_isnumber(L, -1))
			file << lua_tonumber(L, -1) << ",";
		else if (lua_isboolean(L, -1))
			file << (lua_toboolean(L, -1) ? "true," : "false,");
		else
			file << "null,";

		lua_pop(L, 1);
	}
	file << "\n}";

	file.close();
	std::cout << "Table saved to " << filename << std::endl;
}