#include "menuItemImage.h"

bool LE::menuItemImage(std::vector<Texture>& guii, const char* label, std::string guiIconName, const char* desc, bool verticalMenu, bool enabled)
{
    size_t menuW = 14;
    size_t menuH = 14;

    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 label_size; // set in next fix

    ImGuiWindow* backed_nav_window = g.NavWindow;

    // --
    bool pressed;
    ImGui::PushID(label);
    if (!enabled)
        ImGui::BeginDisabled();

        // menu button size
        size_t ImageW = (menuW/2);
        if (label[0] == '#' && label[1] == '#') // no label fix
            label = "";
        else
            ImageW = menuW;
        label_size = ImGui::CalcTextSize(label, NULL, true);

    const ImGuiSelectableFlags selectable_flags = ImGuiSelectableFlags_SelectOnRelease | ImGuiSelectableFlags_SetNavIdOnHover;
    const ImGuiMenuColumns* offsets = &window->DC.MenuColumns;

        // --
        float W = label_size.x;
        window->DC.CursorPos.x += IM_FLOOR(style.ItemSpacing.x * 0.5f);
        ImVec2 text_pos(window->DC.CursorPos.x + offsets->OffsetLabel, window->DC.CursorPos.y + window->DC.CurrLineTextBaseOffset);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(style.ItemSpacing.x * 2.0f, style.ItemSpacing.y));

        if (!verticalMenu)
            pressed = ImGui::Selectable("", false, selectable_flags, ImVec2(W+ImageW, 0.0f));
        else
            pressed = ImGui::Selectable("", false, selectable_flags | ImGuiSelectableFlags_SpanAvailWidth, ImVec2(W+ImageW, 0.0f));

        ImGui::PopStyleVar();

            window->DrawList->AddImage(ImTextureID(getTextureNum(guii, guiIconName).value), ImVec2(pos.x, text_pos.y), ImVec2(pos.x+menuW, text_pos.y+menuH));
        
        if (label != "") // no label fix
            ImGui::RenderText(ImVec2(text_pos.x+16, text_pos.y), label);
        //window->DC.CursorPos.x += IM_FLOOR(style.ItemSpacing.x * (-1.0f + 0.5f));

    if (desc != "")
    LE::HelpMarker(desc, false); // button description

    if (!enabled)
        ImGui::EndDisabled();
    ImGui::PopID();

    return pressed;
}