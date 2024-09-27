#pragma once
#include <iostream>
#include <iomanip>
#include <sstream>

namespace LE
{
	// F -> 15
	int hexCharToInt(char N);
	// 255 -> FF
	std::string octToHex(std::string Str);
	// FF -> 255
	std::string hexToOct(std::string Str);
}