#include "Editor.h"

void LE::Editor::window_nodeEditor(std::string name)
{
    if (!firstHudDraw) // first draw
    {
        ImGuiID MainID_Central = ImGui::DockBuilderGetCentralNode(backgroundDockSpace)->ID;
        ImGui::SetNextWindowDockID(MainID_Central);
    }
    //
    ImGui::Begin(("Node editor - "+name).c_str(), NULL, ImGuiWindowFlags_MenuBar);

    ImGui::End();
}