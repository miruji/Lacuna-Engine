#include "Editor.h"

void LE::Editor::popup_createNewProject()
{
    //
    if (ImGui::BeginPopupModal("Create New Project", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove))
    {
    ImGui::SetWindowSize(ImVec2(702, 432));
    ImGui::SetWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x/2-ImGui::GetWindowWidth()/2, ImGui::GetIO().DisplaySize.y/2-ImGui::GetWindowHeight()/2));

            // project name
            ImGui::Text("Project name\n");
            static char ProjectNameInput[64];
            ImGui::SetCursorPos(ImVec2(100, 25));
            ImGui::SetNextItemWidth(220);
            ImGui::InputText("##createNewProject_name", ProjectNameInput, 64);

            // platform
            {
                ImVec2 pos = ImGui::GetCursorPos();
                ImGui::Text("Platform: Windows");

                bool* x86;
                bool* x64;
                x86 = new bool(project_architectureBuffer == 1 || project_architectureBuffer == 3);
                x64 = new bool(project_architectureBuffer == 2 || project_architectureBuffer == 3);

                ImGui::SetCursorPos(ImVec2(pos.x+ImGui::CalcTextSize("Platform: Windows").x+10, pos.y));
                if (ImGui::Checkbox("x86", x86))
                {
                    if (*x86 && *x64)
                        project_architectureBuffer = 3;
                    else
                    if (*x86)
                        project_architectureBuffer = 1;
                    else
                    if (*x64)
                        project_architectureBuffer = 2;
                    else
                        project_architectureBuffer = 0;
                }
                ImGui::SetCursorPos(ImVec2(pos.x+ImGui::CalcTextSize("Platform: Windows").x+62, pos.y));
                if (ImGui::Checkbox("x64", x64))
                {
                    if (*x86 && *x64)
                        project_architectureBuffer = 3;
                    else
                    if (*x64)
                        project_architectureBuffer = 2;
                    else
                    if (*x86)
                        project_architectureBuffer = 1;
                    else
                        project_architectureBuffer = 0;
                }
            }

            //
            ImGui::SetNextWindowPos( ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y+(432-64)) );
            ImGui::BeginChild("##createNewProject_bottom", ImVec2(702, 64), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove);
                //ImGui::Text("\nDirectory of the projects:\n");
                //ImGui::Text((EngineData[2]+"\n").c_str());
                size_t TextSize = engine_data[2].length()+1;
                char* Text2 = new char[TextSize];
                strcpy_s(Text2, TextSize, engine_data[2].c_str());
                ImGui::SetCursorPos(ImVec2(20, 22));
                ImGui::SetNextItemWidth(424);
                ImGui::InputText("", Text2, TextSize, ImGuiInputTextFlags_ReadOnly);
                
                ImGui::SetCursorPos( ImVec2(702-(104+16), 16) );
                if (ImGui::Button("Back", ImVec2(104, 32)))
                    openNextPopup("Project list");
                
                ImGui::SetCursorPos( ImVec2(702-(208+32), 16) );
                if (ImGui::Button("Create", ImVec2(104, 32)))
                if (testProjectPathName(ProjectNameInput) && project_architectureBuffer)
                {
                    closePopup();
                    //
                    closeProject(false);
                    if (createNewProject(ProjectNameInput))
                        openProject({"t", project_root+"project.lep"});
                    else
                        openNextPopup("New Project Exist");
                    
                    ProjectNameInput[0] = '\0';
                }
                
            ImGui::EndChild();
        //
        ImGui::EndPopup();
    }
    //
}