#pragma once
#include <iostream>
#include <vector>
#include <string>

#include <ImGUI/imgui.h>
#include "ImGUI/imgui_internal.h"

#include "../../Graphics/GUI/GUI.h"

namespace LE {
	class ImageEditor
	{
	private:

	public:
		bool show = true;
		std::string name = "None";

		ImageEditor(std::string name);
		void draw(std::vector<Texture>& guii, ImGuiStyle* guis);
	};
}