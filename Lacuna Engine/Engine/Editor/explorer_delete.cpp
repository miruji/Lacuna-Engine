#include "Editor.h"

// delete any file
void LE::Editor::explorer_delete()
{
    std::vector<std::string> name = cutBackNumber(explorer_name, '~');
    std::string fileName;

    if (explorer_type == "object")
    {
        fileName = getFileName( project_importFile.getImport(project_importFile.objects, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.objects, name[0]);
    }
    else
    if (explorer_type == "scene")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.scenes, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.scenes, name[0]);
    }
    else
    if (explorer_type == "texture")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.textures, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.textures, name[0]);
    }
    else
    if (explorer_type == "animation")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.animations, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.animations, name[0]);
    }
    else
    if (explorer_type == "font")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.fonts, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.fonts, name[0]);
    }
    else
    if (explorer_type == "shader")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.shaders, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.shaders, name[0]);
    }
    else
    if (explorer_type == "sound")
    {
        fileName = getFileName(project_importFile.getImport(project_importFile.sounds, name[0]).path )[0];
        project_importFile.deleteImport(project_importFile.sounds, name[0]);
    }
    //
    {
        std::string p = project_import+fileName+".import";
        l.push("i1","Delete file: ["+p+"]");
        fs::remove(p);

                    p = project_root+explorer_type+"s\\"+fileName;
        l.push("i1", "Delete file: ["+p+"]");
        fs::remove(p);

        l.push("c", "");
    }
    explorer_name = "";
    explorer_type = "";
}