#pragma once
#include <iostream>
#include <vector>
#include <Windows.h>

#include "../Func/wideStringConvert.h"

namespace LE
{
    std::vector<std::string> getFilesList(std::string filePath, std::vector<std::string> extension);
}