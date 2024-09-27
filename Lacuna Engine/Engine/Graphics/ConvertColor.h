#pragma once
#include <iostream>
#include <vector>

#define  GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#include <ImGUI/imgui.h>
#include "../Graphics/FloatMacro.h"

#include "../Func/splitString.h"
#include "../Func/noSpaces.h"
#include "../Func/toUpperCase.h"
#include "../Func/octHex.h"

namespace LE
{
	std::vector<std::string> colorType(std::string c);
	std::vector<float> convertColor(std::string c);
}