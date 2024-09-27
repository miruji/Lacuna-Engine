#include "getFileReplaceAll.h"

std::string LE::getFileReplaceAll(std::string File, std::string const ToReplace, std::string const ReplaceWith)
{
    std::string Buffer = "";
    std::ifstream F(File);
    if (F.is_open())
    {
        std::string Line;
        while (std::getline(F, Line))
            Buffer += Line;
    }
    F.close();

    replaceAll(Buffer, ToReplace, ReplaceWith);
    return Buffer;
}