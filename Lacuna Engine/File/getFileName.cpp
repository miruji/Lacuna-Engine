#include "getFileName.h"

std::vector<std::string> LE::getFileName(std::string Path)
{
	std::string Result = "";
	size_t PathCut = 0;
	for (size_t i = 0; i < Path.length(); i++)
	{
		if (Path[i] == '\\' || Path[i] == '/')
		{
			Result = "";
			PathCut = i+1;
		}
		else
			Result += Path[i];
	}
	return {Result, std::to_string(PathCut)};
}