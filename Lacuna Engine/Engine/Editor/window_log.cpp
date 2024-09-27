#include "Editor.h"

void LE::Editor::window_log()
{
    ImGui::Begin("Log", NULL, ImGuiWindowFlags_MenuBar);
    if (ImGui::BeginMenuBar())
    {
        if (menuItemImage("##log_save", "saveFile", "Save log"))
        {
            l.push("w", "TO:DO: Save log!"); // TO:DO:
            l.push("w", "TO:DO: Save log!"); // TO:DO:
            l.push("w", "TO:DO: Save log!"); // TO:DO:
        }
        ImGui::EndMenuBar();
    }
    l.draw(guii, guis);
    ImGui::End();
}