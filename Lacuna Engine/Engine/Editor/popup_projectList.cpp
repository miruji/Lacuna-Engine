#include "Editor.h"

void LE::Editor::popup_projectList()
{
    //
    ImGui::SetNextWindowSize(ImVec2(702, 432));
    if (ImGui::BeginPopupModal("Project list", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));
            // all projects
            ImGui::Text("All projects\n");
            ImGui::Separator();

            if (allProjectsPlatform.size() == 0) // reopen file list
            {
            allProjectsList = getFolderList( engine_data[2] );
            for (size_t i = 0; i < allProjectsList.size(); i++)
            {
                size_t Architecture = atoi( getLuaFileVars(allProjectsList[i]+"\\project.lep", {"project_architecture"})[0].c_str() );
                allProjectsPlatform.emplace_back(Architecture);
            } }
            ImGui::BeginChild("##projectList", ImVec2(484, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);
            for (size_t i = 0; i < allProjectsList.size(); i++) // draw file list
            {
                if (ImGui::BeginChild(("##projectList_"+std::to_string(i)).c_str(), ImVec2(468, 48), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse))
                {
                    ImGui::SetCursorPos(ImVec2(8, 10));
                    ImGui::Image(ImTextureID(getTextureNum(guii, "projectList").value), ImVec2(28, 28));
                    ImGui::SetCursorPos(ImVec2(40, 9));
                    {
                        std::vector<std::string> N = splitString(allProjectsList[i], '\\');
                        ImGui::Text((N[N.size()-1]).c_str());
                    }
                    ImGui::SetCursorPos(ImVec2(40, 25));

                    std::string Platform = "Platform: ";
                    if (allProjectsPlatform[i] == 1)
                        Platform += "x86";
                    else
                    if (allProjectsPlatform[i] == 2)
                        Platform += "x64";
                    else
                    if (allProjectsPlatform[i] == 3)
                        Platform += "x86/x64";
                    ImGui::Text(Platform.c_str());

                    ImGui::SetCursorPos(ImVec2(399, 25));
                    if (ImGui::Button("Delete", ImVec2(64, 18)))
                    {
                        allProjectsDelete = allProjectsList[i];
                        openNextPopup("Delete project", false);
                    }
                    ImGui::SetCursorPos(ImVec2(331, 25));
                    if (ImGui::Button("Open", ImVec2(64, 18)))
                    {
                        closeProject(false);
                        openProject({"t", allProjectsList[i]+"\\project.lep"});

                        closePopup();
                    }
                    ImGui::SetCursorPos(ImVec2(303, 25));
                    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 4));
                    if ( ImGui::ImageButton(ImTextureID(getTextureNum(guii, "settings").value), ImVec2(20, 10)) )
                    {
                        l.push("w", "TO:DO: Project settings!"); // TO:DO:
                        l.push("w", "TO:DO: Project settings!"); // TO:DO:
                        l.push("w", "TO:DO: Project settings!"); // TO:DO:
                    }
                    ImGui::PopStyleVar();

                    ImGui::EndChild();
                }
            }
            ImGui::EndChild();

            // func
            ImGui::SetNextWindowPos(ImVec2(ImGui::GetWindowPos().x+702-210, ImGui::GetWindowPos().y+19));
            ImGui::BeginChild("##projectList_Right", ImVec2(222, 432), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
            ImGui::Text("Functions");

            ImGui::SetCursorPosY(29);
            if (ImGui::Button("New project", ImVec2(198, 32)))
                openNextPopup("Create New Project");

            if (ImGui::Button("Import project", ImVec2(198, 32)))
            {
                if( openProject() )
                    closePopup();
            }

            if (project_name != "~")
            {
                ImGui::SetCursorPos(ImVec2(100, 374));
                if (ImGui::Button("Close", ImVec2(104, 32)))
                    closePopup();
            }

            ImGui::EndChild();

        //
        ImGui::EndPopup();
    }
    //
}