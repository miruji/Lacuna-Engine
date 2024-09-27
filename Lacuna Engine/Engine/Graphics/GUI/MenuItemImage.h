#pragma once
#include <iostream>

#include <ImGUI/imgui.h>
#include "ImGUI/imgui_internal.h"

#include "../Func/cutBackNumber.h"
#include "HelpMarker.h"
#include "../Texture.h"

namespace LE
{
	bool menuItemImage(std::vector<Texture>& guii, const char* label, std::string guiIconName, const char* desc = "", bool verticalMenu = false, bool enabled = true);
}