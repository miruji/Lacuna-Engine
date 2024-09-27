#pragma once
#include <iostream>

#include <ImGUI/imgui.h>
#include "ImGUI/imgui_internal.h"

#include "../Func/cutBackNumber.h"
#include "../FloatMacro.h"
#include "../Texture.h"

namespace LE
{
	bool treeNodeImage(std::vector<Texture>& guii, std::string label, std::string guiIconName, size_t& click, bool selected = false, bool addButton = false, bool arrow = true, size_t doubleClick = 0, std::string dragAndDrop = "");
}