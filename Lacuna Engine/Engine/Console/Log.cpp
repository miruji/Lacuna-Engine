#include "Log.h"

LE::Log::Log()
{
}
LE::Log::~Log()
{
}
void LE::Log::push(std::string type, std::string data)
{
    if (type != "ls" &&
        type != "i1" &&
        type != "i2" &&
        type != "e" &&
        type != "w" &&
        type != "p" &&
        type != "c"
       )
        type = "i1";

    std::string typeStr;
    if (type == "ls") typeStr = ""; else
    if (type == "i1") typeStr = "[info] "; else
    if (type == "i2") typeStr = "[import] "; else
    if (type == "e")  typeStr = "[error] "; else
    if (type == "w")  typeStr = "[warning] "; else
    if (type == "p")  typeStr = ""; else
    if (type == "c")  typeStr = "";

    std::string lineDataTime = "["+GetDate()+" "+GetTime(":")+"] ";
    std::string lineData = typeStr+data;
    if (list.size() > 0 && list[list.size()-1].beginData == lineData)
        list[list.size()-1].anotherOne();
    else
    {
        list.emplace_back(Line(lineDataTime, type, lineData));
        std::cout << list[list.size()-1].data << "\n"; // to basic console
    }
    updateScrollY = true;
}
// ImGui window draw
void LE::Log::draw(std::vector<Texture>& guii, ImGuiStyle* guis)
{
    // ---------------------------------------------------------------
    //    blue = { 0.000f, 0.703f, 0.917f,1 },
    //    red = { 0.976f, 0.117f, 0.265f ,1 },
    //    grey = { 0.230f, 0.226f, 0.289f,1 },
    //    lgrey = { 0.630f, 0.626f, 0.689f,1 },
    //    green = { 0.000f, 0.386f, 0.265f,1 },
    //    lime = { 0.55f, 0.90f, 0.06f,1 },
    //    yellow = { 0.91f, 1.00f, 0.21f,1 },
    //    purple = { 1,0,1,1 },
    //    orange = { 1.00f, 0.36f, 0.09f,1 };
    // ---------------------------------------------------------------
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    for (size_t i = 0; i < list.size(); i++)
    {
        const auto& type = list[i].type;
        ImGui::PushStyleColor(ImGuiCol_Text,
            (type == "ls") ? LogStartedColor :
            (type == "i2") ? ImportColor :
            (type == "e") ? ErrorColor :
            (type == "w") ? WarningColor :
            (type == "p") ? ProjectColor :
            (type == "c") ? ContinueColor :
            TextColor
        );
        const auto& Data = list[i].data;
        logLine(guii, Data.c_str(),
            (type == "ls") ? "log_started" :
            (type == "i2") ? "log_import" :
            (type == "e") ? "log_error" :
            (type == "w") ? "log_warning" :
            (type == "p") ? "log_project" :
            (type == "c") ? "log_continue" :
            "log_line", i
        );
        ImGui::PopStyleColor();
    }
    ImGui::PopStyleColor();

    if (updateScrollY || !updateScrollYSecond)
    {
        int y = ImGui::GetScrollY(), ym = ImGui::GetScrollMaxY();
        if (y == ym)
        {
            ImGui::SetScrollY(ym);
            updateScrollYSecond = true;
        }
        if (y < ym)
        {
            ImGui::SetScrollY(ym);
            updateScrollY = false;
            updateScrollYSecond = false;
        }
    }

    // copy popup
    if (logLineRightClick > 0)
    {
        if (logLineFirst)
        {
            ImGui::OpenPopup("Log Copy Line");
            logLineFirst = false;
        }

        if (ImGui::BeginPopupContextItem("Log Copy Line"))
        {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            if (ImGui::Button("Copy", ImVec2(64, 18)))
            {
                ImGui::LogToClipboard();
                ImGui::LogText(list[logLineRightClick - 1].data.c_str());
                ImGui::LogFinish();
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleColor();
            ImGui::EndPopup();
        }
        else if (!logLineFirst)
        {
            logLineRightClick = 0;
            logLineFirst = true;
        }
    }
    //
}
// to .log file
std::string LE::Log::getFileName()
{
    return GetDate()+" "+GetTime(".") + ".log";
}
// save new log file
void LE::Log::saveFile()
{
    if (!LE::dirExist("Log")) LE::newDirectory("Log");

    std::string filePath = getRootPath() + "\\Log\\" + getFileName();

        push("c", "");
        push("ls", "[Engine closed]");
        push("i1", "Log saved in \""+ filePath +"\"");
    
    if (!LE::fileExist(filePath))
    {
        std::vector<std::string> list;
        for (size_t i = 0; i < this->list.size(); i++)
            list.emplace_back(this->list[i].data);
        newFile(filePath, list);
        // --
    }
}
//
void LE::Log::logLine(std::vector<Texture>& guii, const char* label, std::string guiIconName, size_t i, bool enabled)
{
    const size_t menuW = 14;
    const size_t menuH = 14;

    ImGuiWindow* window = ImGui::GetCurrentWindow();

    ImGuiContext& g = *GImGui;
    ImGuiStyle& style = g.Style;
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 label_size; // set in next fix

    ImGuiWindow* backed_nav_window = g.NavWindow;

    // --
    ImGui::PushID(label);
    if (!enabled)
        ImGui::BeginDisabled();

    // menu button size
    size_t ImageW = (menuW / 2);
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
    ImGui::Selectable("", false, selectable_flags, ImVec2(W + ImageW, 0.0f));
    ImGui::PopStyleVar();

    window->DrawList->AddImage(ImTextureID(getTextureNum(guii, guiIconName).value), ImVec2(pos.x, text_pos.y), ImVec2(pos.x + menuW, text_pos.y + menuH));

    if (label != "") // no label fix
        ImGui::RenderText(ImVec2(text_pos.x + 16, text_pos.y), label);

    // --
    if (ImGui::IsItemClicked(1) && ImGui::IsItemHovered())
        logLineRightClick = i + 1;

    if (!enabled)
        ImGui::EndDisabled();
    ImGui::PopID();
}