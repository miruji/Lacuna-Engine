#include "newFile.h"

void LE::newFile(const std::string& FilePath, const std::vector<std::string>& FileData)
{
    std::ofstream F(FilePath);
    if (F)
    for (const auto& line : FileData)
        F << line << '\n';
}
