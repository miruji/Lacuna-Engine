#include "Editor.h"

void LE::Editor::popup_fileExist()
{
    //
    ImGui::SetNextWindowSize(ImVec2(312, 96));
    if (ImGui::BeginPopupModal("Project Explorer File Exist", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));
        
        ImGui::TextWrapped("Such file already exists, to add create a new one");
        //if (ImGui::Button("Reload", ImVec2(64, 18)))
        //{
        //    ImGui::CloseCurrentPopup();
        //}
        ImGui::SetCursorPos(ImVec2(240, 64));
        if (ImGui::Button("Ok", ImVec2(64, 18)))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    //
}