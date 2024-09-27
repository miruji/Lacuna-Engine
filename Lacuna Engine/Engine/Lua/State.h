#pragma once
#include <iostream>
#include <luajit/lua.hpp> // lua

#include "json.h"
#include <fstream>

namespace LE
{
	//
	class State
	{
	private:
		lua_State* L;

	public:
		State();
		~State();
		void del();
		
		std::string fileName;
		inline lua_State* getLuaState() { return L; }

		int loadFile(const char* fileName);
		int func(const char* name);
		int num(const char* name);
		std::string str(const char* name);
		std::string getTableString(const char* tableName, const char* key);

		void jsonTable(const std::string& tableName, const std::string& Str);

		void printAll(int level = 0);
		void save(const char* filename);
	};
}