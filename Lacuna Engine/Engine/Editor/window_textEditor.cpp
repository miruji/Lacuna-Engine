#include "Editor.h"

void LE::Editor::window_textEditor(std::string name)
{
    if (!firstHudDraw) // first draw
    {
        ImGuiID MainID_Central = ImGui::DockBuilderGetCentralNode(backgroundDockSpace)->ID;
        ImGui::SetNextWindowDockID(MainID_Central);
    }
    //
    ImGui::Begin(("Text editor - "+name).c_str(), NULL, ImGuiWindowFlags_MenuBar);

    ImGui::End();
}