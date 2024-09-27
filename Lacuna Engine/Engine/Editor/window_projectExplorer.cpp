#include "Editor.h"

void LE::Editor::window_projectExplorer()
{
    ImGui::Begin("Project explorer");
    size_t c1 = false; // main click
        // ==========================================================
        if (treeNodeImage("scripts", "explorer_folder", c1, false, false))
        {
            size_t c2 = false; // click
            if (treeNodeImage("objects", "explorer_component", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.objects.size(); i++)
                if (project_importFile.objects[i].type == "object")
                {
                    size_t c3 = false; // click
                    std::string nodeName = project_importFile.objects[i].name+"~objects_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;
                    if(treeNodeImage(nodeName, "explorer_script", c3, selected, false, false, 2, project_importFile.objects[i].name+"~Object"))
                        ImGui::TreePop();
                    if (c3 && c1 != 1 && c2 != 1)
                    {
                        if (c3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (c3 == 2)
                        {
                            std::cout << "1 Open: " << ProjectImport.Objects[i].Name << " : " << c3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Objects[i].Name;
                            Properties_Type = "Object";
                            std::cout << "1 Properties: " << ProjectImport.Objects[i].Name << " : " << c3 << std::endl;
                        }
                        */
                        explorer_type = "object";
                        explorer_name = nodeName;
                        c3 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Object" << std::endl;
                    explorer_type = "object";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            if (treeNodeImage("scenes", "explorer_scene0", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.scenes.size(); i++)
                if (project_importFile.scenes[i].type == "scene")
                {
                    size_t c3 = false; // click
                    std::string nodeName = project_importFile.scenes[i].name+"~scenes_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;

                    if(treeNodeImage(nodeName, "explorer_scene1", c3, selected, false, false, 2))
                        ImGui::TreePop();
                    if (c3 && c1 != 1 && c2 != 1)
                    {
                        if (c3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (c3 == 2)
                        {
                            std::cout << "2 Open: " << ProjectImport.Scenes[i].Name << " : " << c3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Scenes[i].Name;
                            Properties_Type = "Scene";
                            std::cout << "2 Properties: " << ProjectImport.Scenes[i].Name << " : " << c3 << std::endl;
                        }
                        */
                        explorer_type = "scene";
                        explorer_name = nodeName;
                        c3 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Scene" << std::endl;
                    explorer_type = "scene";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            ImGui::TreePop();
        }
        // ==========================================================
        if (treeNodeImage("graphics", "explorer_folder", c1, false, false))
        {
            size_t c2 = false; // click
            if (treeNodeImage("textures", "explorer_texture", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.textures.size(); i++)
                if (project_importFile.textures[i].type == "texture")
                {
                    size_t Ñ3 = false; // click
                    std::string nodeName = project_importFile.textures[i].name+"~textures_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;

                    if(treeNodeImage(nodeName, "explorer_empty", Ñ3, selected, false, false, 2))
                        ImGui::TreePop();
                    if (Ñ3 && c1 != 1 && c2 != 1)
                    {
                        if (Ñ3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (Ñ3 == 2)
                        {
                            std::cout << "3 Open: " << ProjectImport.Textures[i].Name << " : " << Ñ3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Textures[i].Name;
                            Properties_Type = "Texture";
                            std::cout << "3 Properties: " << ProjectImport.Textures[i].Name << " : " << Ñ3 << std::endl;
                        }
                        */
                        explorer_type = "texture";
                        explorer_name = nodeName;
                        Ñ3 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Texture" << std::endl;
                    explorer_type = "texture";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            if (treeNodeImage("animations", "explorer_animation", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.animations.size(); i++)
                if (project_importFile.animations[i].type == "animation")
                {
                    size_t c3 = false; // click
                    std::string nodeName = project_importFile.animations[i].name+"~animations_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;

                    if(treeNodeImage(nodeName, "explorer_empty", c3, selected, false, false, 2))
                        ImGui::TreePop();
                    if (c3 && c1 != 1 && c2 != 1)
                    {
                        if (c3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (c3 == 2)
                        {
                            std::cout << "4 Open: " << ProjectImport.Animations[i].Name << " : " << c3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Animations[i].Name;
                            Properties_Type = "Animation";
                            std::cout << "4 Properties: " << ProjectImport.Animations[i].Name << " : " << c3 << std::endl;
                        }
                        */
                        explorer_type = "animation";
                        explorer_name = nodeName;
                        c1 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Animation" << std::endl;
                    explorer_type = "animation";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            if (treeNodeImage("fonts", "explorer_font", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.fonts.size(); i++)
                if (project_importFile.fonts[i].type == "font")
                {
                    size_t c3 = false; // click
                    std::string nodeName = project_importFile.fonts[i].name+"~fonts_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;

                    if(treeNodeImage(nodeName, "explorer_empty", c3, selected, false, false, 2))
                        ImGui::TreePop();
                    if (c3 && c1 != 1 && c2 != 1)
                    {
                        if (c3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (c3 == 2)
                        {
                            std::cout << "5 Open: " << ProjectImport.Fonts[i].Name << " : " << c3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Fonts[i].Name;
                            Properties_Type = "Font";
                            std::cout << "5 Properties: " << ProjectImport.Fonts[i].Name << " : " << c3 << std::endl;
                        }
                        */
                        explorer_type = "font";
                        explorer_name = nodeName;
                        c3 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Font" << std::endl;
                    explorer_type = "font";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            if (treeNodeImage("shaders", "explorer_shader", c2, false, true))
            {
                for (size_t i = 0; i < project_importFile.shaders.size(); i++)
                if (project_importFile.shaders[i].type == "shader")
                {
                    size_t c3 = false; // click
                    std::string nodeName = project_importFile.shaders[i].name+"~shaders_"+std::to_string(i);
                    bool selected = false;
                    if (explorer_name == nodeName) selected = true;

                    if(treeNodeImage(nodeName, "explorer_empty", c3, selected, false, false, 2))
                        ImGui::TreePop();
                    if (c3 && c1 != 1 && c2 != 1)
                    {
                        if (c3 == 4)
                            openNextPopup("Explorer Context");
                        /*
                        else
                        if (c3 == 2)
                        {
                            std::cout << "6 Open: " << ProjectImport.Shaders[i].Name << " : " << c3 << std::endl;
                        }
                        else
                        {
                            Properties_Name = ProjectImport.Shaders[i].Name;
                            Properties_Type = "Shader";
                            std::cout << "6 Properties: " << ProjectImport.Shaders[i].Name << " : " << c3 << std::endl;
                        }
                        */
                        explorer_type = "shader";
                        explorer_name = nodeName;
                        c3 = false;
                    }
                }
                ImGui::TreePop();
            }
                if (c2 == 3)
                {
                    std::cout << "Click: Add Shader" << std::endl;
                    explorer_type = "shader";
                    openNextPopup("Explorer Add Context");
                    c2 = false;
                }
            ImGui::TreePop();
        }
        // ==========================================================
        if (treeNodeImage("sounds", "explorer_folder", c1, false, true))
        {
            size_t c2 = false; // click
            for (size_t i = 0; i < project_importFile.sounds.size(); i++)
            if (project_importFile.sounds[i].type == "sound")
            {
                size_t c3 = false; // click
                std::string nodeName = project_importFile.sounds[i].name+"~sounds_"+std::to_string(i);
                bool selected = false;
                if (explorer_name == nodeName) selected = true;

                if(treeNodeImage(nodeName, "explorer_empty", c3, selected, false, false, 2))
                    ImGui::TreePop();
                if (c3 && c1 != 1 && c2 != 1)
                {
                    if (c3 == 4)
                        openNextPopup("Explorer Context");
                    /*
                    else
                    if (c3 == 2)
                    {
                        std::cout << "7 Open: " << ProjectImport.Sounds[i].Name << " : " << c3 << std::endl;
                    }
                    else
                    {
                        Properties_Name = ProjectImport.Sounds[i].Name;
                        Properties_Type = "Sound";
                        std::cout << "7 Properties: " << ProjectImport.Sounds[i].Name << " : " << c3 << std::endl;
                    }
                    */
                    explorer_type = "sound";
                    explorer_name = nodeName;
                    c3 = false;
                }
            }
            ImGui::TreePop();
        }
            if (c1 == 3)
            {
                std::cout << "Click: Add Sound" << std::endl;
                explorer_type = "sound";
                openNextPopup("Explorer Add Context");
                c1 = false;
            }
        // ==========================================================
    ImGui::End();
}