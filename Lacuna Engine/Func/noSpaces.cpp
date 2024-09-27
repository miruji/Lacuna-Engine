#include "noSpaces.h"

std::string LE::noSpaces(std::string Str)
{
	std::string Result;
	for (size_t i = 0; i < Str.length(); i++)
	if (Str[i] != ' ') Result += Str[i];

	return Result;
}