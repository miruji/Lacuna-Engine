#include "getNameNum.h"

std::vector<std::string> LE::getNameNum(std::string Name)
{
    std::string BackNum;
    size_t NameCut = 0;

    for (size_t i = Name.length() - 1; i > 0; i--)
    {
        if (!isInt(Name[i]))
        {
            BackNum = "";
            NameCut = Name.length();
            break;
        }
        BackNum += Name[i];
        if (isChar(Name[i]) || Name[i] == ' ')
        {
            NameCut = i;
            break;
        }
    }
    return {BackNum, std::to_string(NameCut)};
}