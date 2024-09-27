#include "TreeNodeImage.h"

bool LE::treeNodeImage(std::vector<Texture>& guii, std::string label, std::string guiIconName, size_t& click, bool selected, bool addButton, bool arrow, size_t doubleClick, std::string dragAndDrop)
{
    ImGuiStyle& guis = ImGui::GetStyle(); (void)guis;
    guis.ItemSpacing = ImVec2(0, 4);

    ImGuiContext& g = *GImGui;
    ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImU32 id = window->GetID(label.c_str());
    std::string Label2 = cutBackNumber(label, '~')[0]; // no back

    ImVec2 pos = window->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x+ImGui::GetContentRegionAvail().x, pos.y+ImGui::GetFontSize() + guis.FramePadding.y*2));

    bool isOpen = ImGui::TreeNodeBehaviorIsOpen(id);
    if (isOpen && !g.NavIdIsAlive && (ImGuiTreeNodeFlags_NavLeftJumpsBackHere) && !(ImGuiTreeNodeFlags_NoTreePushOnOpen))
        window->DC.TreeJumpToParentOnPopMask |= (1 << window->DC.TreeDepth);

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    bool itemAdd = ImGui::ItemAdd(bb, id);
    g.LastItemData.StatusFlags |= ImGuiItemStatusFlags_HasDisplayRect;
    g.LastItemData.DisplayRect = bb;

    if (hovered || selected)
    {
        ImU32 bgColor;
        if (selected)
        {
            bgColor = ImGui::GetColorU32((selected && hovered) ? ImGuiCol_HeaderHovered : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
        }
        else
            bgColor = ImGui::GetColorU32((held && hovered) ? ImGuiCol_HeaderActive : hovered ? ImGuiCol_HeaderHovered : ImGuiCol_Header);
        ImGui::RenderFrame(bb.Min, bb.Max, bgColor, guis.FrameRounding);
    }

    if (dragAndDrop.length())
    {
        if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID | ImGuiButtonFlags_PressedOnDragDropHold))
        {
            ImGui::SetDragDropPayload("STRING", dragAndDrop.c_str(), dragAndDrop.length()+1, ImGuiDragDropFlags_SourceNoPreviewTooltip);

            ImGui::Image(ImTextureID(getTextureNum(guii, guiIconName).value), ImVec2(12, 12));
            ImGui::SetCursorPos(ImVec2(ImGui::GetCursorPosX() + 18, 5));
            ImGui::Text(cutBackNumber(dragAndDrop, '.')[0].c_str());

            ImGui::EndDragDropSource();
        }
    }

    // Icon, text
    float button_sz = ImGui::GetFontSize() + guis.FramePadding.y*2;
    if (button_sz > 16) button_sz = button_sz*0.9;
    
    pos.x += 4;
    if (arrow)
    {
        if (guiIconName != "")
            window->DrawList->AddImage(ImTextureID(getTextureNum(guii, guiIconName).value), ImVec2(pos.x+button_sz*0.1+14, pos.y+button_sz*0.1), ImVec2(pos.x + button_sz+14, pos.y + button_sz));
        
        ImGui::RenderText(ImVec2(pos.x+button_sz+guis.ItemInnerSpacing.x+17, pos.y+guis.FramePadding.y-1), Label2.c_str());
    }
    else
    {
        if (guiIconName != "")
            window->DrawList->AddImage(ImTextureID(getTextureNum(guii, guiIconName).value), ImVec2(pos.x+button_sz*0.1+10, pos.y+button_sz*0.1), ImVec2(pos.x + button_sz+10, pos.y + button_sz));
        
        ImGui::RenderText(ImVec2(pos.x+button_sz+guis.ItemInnerSpacing.x+13, pos.y+guis.FramePadding.y-1), Label2.c_str());
    }

    // click
    if (ImGui::IsItemClicked(1))
    {
        click = 4;
    }
    else
    if (doubleClick != 1 && ImGui::IsItemClicked(0))
    {
        isOpen = !isOpen;

        click = true;
    }
    if (doubleClick && ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemHovered())
    {
        isOpen = !isOpen;

        click = 2;
    }
    if (click)
        window->DC.StateStorage->SetInt(id, isOpen);
        
        // plus button
        guis.FrameRounding = 32;
        if (addButton)
        {
            ImGui::SetItemAllowOverlap();
            ImGui::SetCursorPosX(button_sz+guis.ItemInnerSpacing.x+ImGui::CalcTextSize(Label2.c_str()).x+24+(bb.Min.x-window->Pos.x));
            ImGui::SetCursorPosY(ImGui::GetCursorPosY()+3);

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(4, 4));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(5, 4));
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 6));

            ImGui::ImageButton(ImTextureID(getTextureNum(guii, "plus").value), ImVec2(6, 6));
            if (ImGui::IsMouseClicked(0) && ImGui::IsItemHovered())
            {
                isOpen = !isOpen;
                window->DC.StateStorage->SetInt(id, isOpen);

                click = 3;
            }

            ImGui::PopStyleVar(3);
        }
        guis.FrameRounding = 0;

    // --
    if (arrow)
        ImGui::RenderArrow(window->DrawList, ImVec2(pos.x, pos.y+ImGui::GetFontSize()/2-1), ImColor(255, 255, 255, 255), isOpen ? ImGuiDir_Down : ImGuiDir_Right, 0.70f);

    if (isOpen)
        ImGui::TreePushOverrideID(id);

    if (!addButton)
        ImGui::Dummy(ImVec2(0.0f, 20.0f));
    guis.ItemSpacing = ImVec2(8, 4);
    return isOpen;
}