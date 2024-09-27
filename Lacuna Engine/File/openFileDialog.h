#pragma once
#include <iostream>
#include <windows.h>

#include "../Func/wideStringConvert.h"

namespace LE
{
	std::string openFileDialog(LPCWSTR Filter, LPCWSTR InitialDir = 0);
}