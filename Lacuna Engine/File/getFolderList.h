#pragma once
#include <filesystem>
namespace fs = std::filesystem;

#include "../Func/wideStringConvert.h"

namespace LE
{
	std::vector<std::string> getFolderList(std::string Dir);
}