#include "Editor.h"

void LE::Editor::popup_explorerContext()
{
    //
    if (ImGui::BeginPopupContextItem("Explorer Context"))
    {
        size_t RegionAvailX = ImGui::GetContentRegionAvail().x;

        if (ImGui::Button("Show in folder", ImVec2(RegionAvailX, 18)))
        {
            explorer_showInFolder();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Rename", ImVec2(RegionAvailX, 18)))
        {
            explorer_rename();
            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Delete", ImVec2(RegionAvailX, 18)))
        {
            openNextPopup("Delete a file", false);
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    //
}