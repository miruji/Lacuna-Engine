#include "createNewFile.h"

void LE::createNewFile(std::string FilePath, std::vector<std::string> FileData)
{
    // --
    std::ofstream F(FilePath);
    if (F.is_open())
    {
        for (size_t i = 0; i < FileData.size(); i++)
            F << FileData[i] << std::endl;
    }
    F.close();
}