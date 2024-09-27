#include "fileExist.h"

bool LE::fileExist(const std::string& Path)
{
	std::ifstream F(Path);
	return F.good();
}