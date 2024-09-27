#include "Editor.h"

void LE::Editor::popup_projectExist()
{
    //
    ImGui::SetNextWindowSize(ImVec2(312, 96));
    if (ImGui::BeginPopupModal("New Project Exist", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));

        ImGui::TextWrapped("Failed to create new project because it already exists");
        ImGui::SetCursorPos(ImVec2(168, 64));

        if (ImGui::Button("Open", ImVec2(64, 18)))
        {
            openProject({"t", project_root+"Project.lep"});
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetCursorPos(ImVec2(240, 64));
        if (ImGui::Button("Ok", ImVec2(64, 18)))
        {
            openNextPopup("Create New Project");
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    //
}