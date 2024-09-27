#include "getFolderList.h"

std::vector<std::string> LE::getFolderList(std::string Dir)
{
    std::vector<std::string> r;
    for (auto& p : fs::directory_iterator(Dir))
    if (p.is_directory())
        r.push_back(p.path().string());
    return r;
}