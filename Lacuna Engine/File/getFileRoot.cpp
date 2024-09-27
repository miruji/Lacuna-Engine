#include "GetFileRoot.h"

std::string LE::getFileRoot(std::string Path)
{
	std::string Result = "";
	std::string Buffer = "";
	for (size_t i = 0; i < Path.length(); i++)
	{
		if (Path[i] == '\\' || Path[i] == '/')
		{
			Buffer += Path[i];
			Result += Buffer;
			Buffer = "";
		}
		else
			Buffer += Path[i];
	}
	return Result;
}