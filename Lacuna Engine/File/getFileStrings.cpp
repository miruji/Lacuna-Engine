#include "getFileStrings.h"

std::vector<std::string> LE::getFileStrings(std::string FilePath)
{
	//std::cout << "#Open File: "+FilePath+"\":" << std::endl;
	//
	std::vector<std::string> Result;
	std::string Str = "";

	// file open 
	std::ifstream File(FilePath);
	if (File.is_open())
	{
		//std::cout << "  > File is open" << std::endl;
		// read file 
		while (getline(File, Str))
			Result.push_back(Str);
	}
	//else
	//{
		//std::cout << "  > File is not open" << std::endl;
	//}

	//
	return Result;
}