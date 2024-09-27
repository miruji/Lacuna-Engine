#include "cutBackNumber.h"

std::vector<std::string> LE::cutBackNumber(std::string String, char Devide)
{
    std::vector<std::string> result;
    size_t i = String.find_last_of(Devide);
    if (i != std::string::npos) {
        result.push_back(String.substr(0, i));
        result.push_back(std::to_string(i));
    }
    else {
        result.push_back(String);
        result.push_back("");
    }
    return result;
}