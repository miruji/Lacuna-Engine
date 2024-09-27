#include "getRootPath.h"

std::string LE::getRootPath()
{
    return std::filesystem::current_path().string();
}