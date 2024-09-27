#include "Editor.h"

void LE::Editor::window_imageEditor(ImageEditor& ie)
{
    if (!firstHudDraw) // first draw
    {
        ImGuiID MainID_Central = ImGui::DockBuilderGetCentralNode(backgroundDockSpace)->ID;
        ImGui::SetNextWindowDockID(MainID_Central);
    }
    //
    ImGui::Begin(("Image editor - "+ie.name).c_str(), &ie.show, ImGuiWindowFlags_MenuBar);
        ie.draw(guii, guis);
    ImGui::End();
}