#include "dirExist.h"

// is dir = true
bool LE::dirExist(const std::string& DirPath)
{
    DWORD attributes = GetFileAttributesA(DirPath.c_str());
    return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}