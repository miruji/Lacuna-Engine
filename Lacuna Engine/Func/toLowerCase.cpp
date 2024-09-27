#include "toLowerCase.h"

std::string LE::toLowerCase(std::string Str)
{
	for (size_t i = 0; i < Str.length(); i++)
	Str[i] = tolower(Str[i]);
	return Str;
}