#include "splitString.h"

std::vector<std::string> LE::splitString(std::string Str, char Split)
{
    std::vector<std::string> Result;
    std::stringstream ss(Str);
    std::string item;
    while (std::getline(ss, item, Split))
        Result.push_back(item);

    return Result;
}