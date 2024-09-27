#pragma once
#include <ImGUI/imgui.h>

namespace
{
	ImVec4 LogStartedColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // white

	ImVec4 ErrorColor    = ImVec4(1.0f, 0.35f, 0.4f, 1.0f);        // pink - red
	ImVec4 WarningColor  = ImVec4(1.000f, 0.824f, 0.349f, 1.000f); // yellow

	ImVec4 ContinueColor = ImVec4(0.97f, 0.9f, 0.57f, 1.0f); // green - sand
	ImVec4 TextColor     = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);   // sand

	ImVec4 ProjectColor = ImVec4(0.349f, 0.800f, 0.604f, 1.000f); // blue (water)
	ImVec4 ImportColor  = ImVec4(0.35f, 0.5f, 0.8f, 1.0f);        // blue
}