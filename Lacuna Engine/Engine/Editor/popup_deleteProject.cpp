#include "Editor.h"

void LE::Editor::popup_deleteProject()
{
    //
    ImGui::SetNextWindowSize(ImVec2(312, 96));
    if (ImGui::BeginPopupModal("Delete project", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));
        
        std::vector<std::string> P = splitString(allProjectsDelete, '\\');
        std::string PName = P[P.size()-1];
        ImGui::TextWrapped(("Are you sure you want to delete the project: "+PName).c_str());

        ImGui::SetCursorPos(ImVec2(168, 64));
        if (ImGui::Button("Yes", ImVec2(64, 18)))
        {
            std::string ProjectNameSave = project_name;
            if (project_name == PName)
                closeProject();

            fs::remove_all(allProjectsDelete);
            allProjectsDelete = "";
            l.push("i1", "Project deleted: "+PName);
            l.push("c", "");

            ImGui::CloseCurrentPopup();
            if (ProjectNameSave != PName)
                openNextPopup(backPopup);
        }
        ImGui::SetCursorPos(ImVec2(240, 64));
        if (ImGui::Button("No", ImVec2(64, 18)))
        {
            ImGui::CloseCurrentPopup();
            openNextPopup(backPopup);
        }

        ImGui::EndPopup();
    }
    //
}