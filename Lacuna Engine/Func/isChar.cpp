#include "isChar.h"

bool LE::isChar(char C)
{
	return (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z');
}