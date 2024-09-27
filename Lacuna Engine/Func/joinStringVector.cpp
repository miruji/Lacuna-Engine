#include "joinStringVector.h"

std::string LE::joinStringVector(std::vector<std::string> Vector)
{
	std::string Result = "";

	for (size_t i = 0; i < Vector.size(); i++)
		Result += Vector[i]+"\n";

	//
	return Result;
}
char* LE::stringVectorToCharArray(const std::string& s)
{
	char* pc = new char[s.size() + 1];
	std::strcpy(pc, s.c_str());
	return pc;
}