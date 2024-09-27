#include "noFileType.h"

std::vector<std::string> LE::noFileType(std::string Path)
{
	std::string Buffer = "";
	std::vector<std::string> Result;
	std::string End = "";
	for (size_t i = 0; i < Path.length(); i++)
	{
		if (Path[i] == '.' || Path[i] == '/' || i+1 == Path.length())
		{
			if (i+1 == Path.length())
				Buffer += Path[i];

			End = std::to_string(i);
			Result.push_back(Buffer);
			Buffer = "";
			break;
		}
		else
			Buffer += Path[i];
	}
	return {Result[0], End};
}