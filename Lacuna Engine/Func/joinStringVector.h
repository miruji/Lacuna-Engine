#pragma once
#pragma warning( disable : 4996)

#include <iostream>
#include <vector>

namespace LE
{
	std::string joinStringVector(std::vector<std::string> Vector);
	char* stringVectorToCharArray(const std::string& s);
}