#include "Editor.h"

void LE::Editor::window_sceneList()
{
    bool dropHover = false;
    ImGui::SetNextWindowSize(ImVec2(200, 200));
    ImGui::Begin("Scene list", 0, ImGuiWindowFlags_NoScrollbar);
        
        ImVec2 dropWindowSize = ImVec2(ImGui::GetWindowWidth(), 42);
        ImVec2 dropWindowPos = ImGui::GetCursorScreenPos();
        ImGui::SetCursorPos(ImVec2(0, 20));
        if (ImGui::BeginChild("##sceneList_dropArea", ImVec2(dropWindowSize.x, dropWindowSize.y), true, ImGuiWindowFlags_NoScrollbar))
        {
            ImVec2 dropAreaPos = ImGui::GetCursorScreenPos();
            ImVec2 dropAreaSize = ImVec2(dropWindowSize.x-12, dropWindowSize.y-10);
            ImGui::InvisibleButton("sceneList_dropAreaButton", dropAreaSize);

            // drop
            if (ImGui::BeginDragDropTarget())
            {
                dropHover = true;
                if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("STRING"))
                {
                    const char* sourceData = static_cast<const char*>(payload->Data);
                    if (sourceData)
                    {
                        std::string scenePath = project_root+"scenes\\main.les";

                        std::string bufferData = sourceData;
                        std::vector<std::string> d = splitString(bufferData, '~');
                        d[0] = cutBackNumber(d[0], '.')[0];
                        std::cout << d[0] <<" : "<< d[1] <<" : "<< scenePath+"\n";
                        std::cout << scene_manager.getCurrentScene().name << "\n";
                        jsonFile f = getJSON(scenePath, R"(
                            {
	                            "name": "scene1",
	                            "objects": []
                            }
                        )");
                        if (f.Created)
                        {
                            f.addObjectTo("objects", { "name: "+d[0], "position: [0, 0]", "size: [24, 24]", "texture: [Textures/Player.png, rgba_f:1,1,1,1]" });
                            scene_list = f.getArray("objects");
                            // TO:DO:
                            // 4. удаление объекта из сцены по названию
                        }
                    }
                }
                ImGui::EndDragDropTarget();
            }
            if (dropHover == false)
            {
                // text size
                ImVec2 textSize = ImGui::CalcTextSize("Drop here");
                ImGui::SetCursorScreenPos(ImVec2(dropAreaPos.x+dropAreaSize.x/2-textSize.x/2,
                    dropAreaPos.y+dropAreaSize.y/2-textSize.y/2));

                // centre text
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 1, 1, 1));
                ImGui::Text("Drop here");
                ImGui::PopStyleColor();
            }

            ImGui::EndChild();
        }

        ImGui::SetCursorPos(ImVec2(0, ImGui::GetCursorPosY()-5));
        if (ImGui::BeginChild("##sceneList_listArea", ImVec2(dropWindowSize.x, ImGui::GetWindowSize().y-ImGui::GetCursorPosY()), true))
        {
            if (scene_list.size())
            {
                size_t c1 = false; // click
                if (treeNodeImage("objects", "explorer_component", c1, false))
                {
                    for (cJSON* o : scene_list) {
                        cJSON* num = cJSON_GetObjectItem(o, "num");
                        cJSON* name = cJSON_GetObjectItem(o, "name");

                        if (num && name) {
                            std::string t = std::to_string(num->valueint) + std::string(": ") + name->valuestring;

                            size_t c2 = false;
                            if (treeNodeImage(t.c_str(), "explorer_script", c2, false, false, false))
                            {
                                ImGui::TreePop();
                            }
                        }
                    }
                }
                //
            }
            else ImGui::Text("Nothing added to the scene");

            ImGui::EndChild();
        }
    ImGui::End();
}