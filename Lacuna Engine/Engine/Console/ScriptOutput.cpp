#include "ScriptOutput.h"
using namespace LE;

ScriptOutput::ScriptOutput()
{
}
ScriptOutput::~ScriptOutput()
{
}
void ScriptOutput::Push(char Type, std::string Data)
{
    if (Type != 'i' && Type != 'e' && Type != 'w' && Type != 'c')
        Type = 'i';
    std::string TypeStr;
    if (Type == 'i') TypeStr = "[info] "; else
    if (Type == 'e') TypeStr = "[error] "; else
    if (Type == 'w') TypeStr = "[warning] "; else
    if (Type == 'c') TypeStr = "";

    List.push_back(Line(Type, "["+GetDate()+" "+GetTime(":")+"] " + TypeStr + Data));
    std::cout << List[List.size()-1].Data << std::endl; // to basic console
}
// ImGui window draw
void ScriptOutput::Draw()
{
    for (size_t i = 0; i < List.size(); i++)
    {
        if (List[i].Type == 'e') ImGui::PushStyleColor(ImGuiCol_Text, ErrorColor); else
        if (List[i].Type == 'w') ImGui::PushStyleColor(ImGuiCol_Text, WarningColor); else
        if (List[i].Type == 'c') ImGui::PushStyleColor(ImGuiCol_Text, ContinueColor);
        else ImGui::PushStyleColor(ImGuiCol_Text, TextColor);

        ImGui::TextUnformatted(List[i].Data.c_str());
        ImGui::PopStyleColor();
    }
}