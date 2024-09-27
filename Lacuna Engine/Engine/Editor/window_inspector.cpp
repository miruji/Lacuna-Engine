#include "Editor.h"

void LE::Editor::window_inspector()
{
    ImGui::Begin("Inspector");
            
        ImVec2 NamePos = ImGui::GetCursorPos();
        ImGui::Text(properties_name.c_str());

        ImVec2 WindowSize = ImGui::GetWindowSize();
        ImGui::SetCursorPos(ImVec2(WindowSize.x-26, NamePos.y));
        if (menuItemImage("##inspector_delete", "delete", "Delete"))
        {
            if (properties_type != "~")
                openNextPopup("Delete a file", false);
        }
        ImGui::SetCursorPos(ImVec2(WindowSize.x-54, NamePos.y));
        if (menuItemImage("##inspector_rename", "edit", "Rename"))
        {
            if (properties_type != "~")
                explorer_rename();
        }
        ImGui::SetCursorPos(ImVec2(WindowSize.x-82, NamePos.y));
        if (menuItemImage("##inspector_showInFolder", "openFolder", "Show in folder"))
        {
            if (properties_type != "~")
                explorer_showInFolder();
        }

        ImGui::SetCursorPos(ImVec2(NamePos.x, NamePos.y+19));
        ImGui::Separator();

        ImGui::Text(("Type: "+properties_type).c_str());
            
    ImGui::End();
}