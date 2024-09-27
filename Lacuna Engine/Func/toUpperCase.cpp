#include "toUpperCase.h"

std::string LE::toUpperCase(std::string Str)
{
	for (size_t i = 0; i < Str.length(); i++)
	Str[i] = toupper(Str[i]);
	return Str;
}