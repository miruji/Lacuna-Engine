#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "../Func/replaceAll.h"

namespace LE
{
    std::string getFileReplaceAll(std::string File, std::string const toReplace, std::string const replaceWith);
}