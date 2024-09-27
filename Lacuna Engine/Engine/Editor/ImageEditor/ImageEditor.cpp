#include "ImageEditor.h"
using namespace LE;

ImageEditor::ImageEditor(std::string name)
{
	this->name = name;
}
void ImageEditor::draw(std::vector<Texture>& guii, ImGuiStyle* guis)
{
    // -- game render top editor
    if (ImGui::BeginMenuBar())
    {
        if (menuItemImage(guii, "##EditorMove", "EditorMove", "Move"))
        {
            std::cout << "EditorMove" << std::endl;
        }
        
        int* size = new int(0);
        ImGui::SetNextItemWidth(196);
        ImGui::SliderInt("##ImageEditorSize", size, 0, 100);

        int* opacity = new int(0);
        ImGui::SetNextItemWidth(196);
        ImGui::SliderInt("##ImageEditorOpacity", opacity, 0, 100);

        ImGui::EndMenuBar();
    }

	ImGui::Text(name.c_str());
}
// ===========================================================================