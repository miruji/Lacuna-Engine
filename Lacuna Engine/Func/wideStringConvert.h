#pragma once
#include <string>
#include <stdexcept>
#include <Windows.h>

namespace LE
{
	// utf8 ->> utf16
	std::wstring stringToWideString(const std::string string);
	// utf16 ->> utf8
	std::string wideStringToString(const std::wstring wide_string);
	//
	LPWSTR convertWideString(const std::string& instr);
	//
	std::string tcharToString(const TCHAR* tcharString);
}