#include "Editor.h"

void LE::Editor::popup_deleteFile()
{
    //
    ImGui::SetNextWindowSize(ImVec2(312, 96));
    if (ImGui::BeginPopupModal("Delete a file", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));
        
        ImGui::TextWrapped(("Are you sure you want to delete the file: "+cutBackNumber(explorer_name, '~')[0]).c_str());

        ImGui::SetCursorPos(ImVec2(96, 64));
        if (ImGui::Button("Remove", ImVec2(64, 18)))
        {
            explorer_remove();
        }
        ImGui::SetCursorPos(ImVec2(168, 64));
        if (ImGui::Button("Delete", ImVec2(64, 18)))
        {
            explorer_delete();
        }
        ImGui::SetCursorPos(ImVec2(240, 64));
        if (ImGui::Button("Cancel", ImVec2(64, 18)))
        {
            closePopup();
        }

        ImGui::EndPopup();
    }
    //
}