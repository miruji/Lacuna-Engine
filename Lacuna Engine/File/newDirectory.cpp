#include "NewDirectory.h"

void LE::newDirectory(std::string PATH)
{
	CreateDirectory(std::wstring(PATH.begin(), PATH.end()).c_str(), NULL);
}