#include "Editor.h"

void LE::Editor::popup_explorerAddContext()
{
    //
    if (ImGui::BeginPopupContextItem("Explorer Add Context"))
    {
        if (explorer_type == "object")
        if (ImGui::Button("Add", ImVec2(64, 18)))
        {
            std::cout << "Project Explorer: Add" << std::endl;

            std::string Name = "New "+explorer_type;
            std::string Import = project_import+Name+".lua.import";
            std::string Object = explorer_type+"s\\\\"+Name+".lua";

            std::vector<std::string> ImportFile = createNewImportFile(Import, Name, explorer_type, Object, true);
            if (ImportFile[0] != "" && ImportFile[1] != "")
            {
                Name = ImportFile[1];
                Import = ImportFile[0];
                // create file
                {
                std::string N = project_root+explorer_type+"s\\"+Name+".lua";
                std::ofstream F(N);
                F << "";
                F.close();

                l.push("i1", "Add new file: ["+N+"]");
                }
                // open import
                openImportFile(Import);
                l.push("c", "");
            }

            ImGui::CloseCurrentPopup();
        }

        if (ImGui::Button("Open", ImVec2(64, 18)))
        {
            std::cout << "Project Explorer: Open" << std::endl;
            std::string Path = "";
            if (explorer_type == "object")
                Path = openFileDialog(L"Object (*.lua)\0*.lua\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "scene")
                Path = openFileDialog(L"Lacuna Engine scene (*.les)\0*.les\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "texture")
                Path = openFileDialog(L"Texture (*.bmp*.png*.jpg*.dds)\0*.bmp;*.png;*.jpg;*.dds\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "animation")
                Path = openFileDialog(L"Lacuna Engine animation (*.lea)\0*.lea\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "font")
                Path = openFileDialog(L"Font (*.otf*.ttf)\0*.otf;*.ttf\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "shader")
                Path = openFileDialog(L"Font (*.frag*.vert)\0*.frag;*.vert\0", stringToWideString(project_root+explorer_type+"s\\").c_str());
            else
            if (explorer_type == "sound")
                Path = openFileDialog(L"Sound (*.ogg*.mp3)\0*.ogg;*.mp3\0", stringToWideString(project_root+explorer_type+"s\\").c_str());

            std::string Name = "";
            std::string Import = "";
            std::string NameType;
            if (Path != "")
            {
                std::vector<std::string> P = getFileName(Path);
                std::vector<std::string> N = noFileType(P[0]);
                Name = N[0];

                NameType = '.' + P[0].substr(atoi(N[1].c_str()) + 1, P[0].size());
                Import = project_import+Name+NameType+".import";
            }
            else
                ImGui::CloseCurrentPopup();
            if (Import != "")
            {
                std::vector<std::string> ImportFile = createNewImportFile(Import, Name, explorer_type, explorer_type+"s\\\\"+Name+NameType, false);
                if (ImportFile[0] != "" && ImportFile[1] != "")
                {
                    Name = ImportFile[1];
                    Import = ImportFile[0];
                    openImportFile(Import);
                    l.push("c", "");
                }
            }
            else
                ImGui::CloseCurrentPopup();
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }
    //
}