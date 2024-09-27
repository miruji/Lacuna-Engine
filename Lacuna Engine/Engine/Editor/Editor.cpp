#include "Editor.h"
using namespace LE;

Editor::Editor(std::string mame, size_t w, size_t h, std::vector<std::string> engine_data) : Window(name, w, h)
{
    // load icons
    this->engine_data = engine_data;

    glfwSetWindowUserPointer(render, this);
}
Editor::Editor() : Window()
{
}
Editor::~Editor()
{
}
void Editor::keyboardCallback(GLFWwindow* render, int key, int scancode, int action, int mods)
{
    Editor* e = static_cast<Editor*>(glfwGetWindowUserPointer(render));

    //
    if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
        glfwSetWindowShouldClose(render, GL_TRUE);
    else
    if (e->scene_started)
    {
        Scene& s = e->scene_manager.getCurrentScene();
        for (size_t i = 0; i < s.k.keys.size(); i++)
        if (key == s.k.keys[i].num && action == GLFW_PRESS)
        {
            s.k.keys[i].pressed = true;
        }
    }
    // WASD & arrow
    // TO:DO: GLFW_RELEASE
    /*
    if ((Key == GLFW_KEY_W || Key == GLFW_KEY_A || Key == GLFW_KEY_S || Key == GLFW_KEY_D)
        && Action == GLFW_PRESS)
    {
        Scene& S = E->SM.GetCurrentScene();
        if (Key == GLFW_KEY_W)
            S.C.Y += S.C.Speed;
        else
        if (Key == GLFW_KEY_A)
            S.C.X += S.C.Speed;
        else
        if (Key == GLFW_KEY_S)
            S.C.Y -= S.C.Speed;
        else
        if (Key == GLFW_KEY_D)
            S.C.X -= S.C.Speed;
    }
    */
}
void Editor::clearRenderFrame()
{
    glClearColor(rgba_to_float(59, 117, 99, 255));      // bg color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // color & depth
}
void Editor::resizeRenderCallback(GLFWwindow* render, int w, int h)
{
    Editor* e = static_cast<Editor*>(glfwGetWindowUserPointer(render));

    // viewport
    glViewport(0, 0, w, h);

    // projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);

    // view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //
    e->renderFrame(render);
}
void Editor::imguiHudStyle()
{
    // imgui styles
    guis = &ImGui::GetStyle();

    guis->Colors[ImGuiCol_Border] = ImVec4(0.595f, 0.781f, 0.661f, 0.388f);

    guis->Colors[ImGuiCol_WindowBg] = ImVec4(0.075f, 0.075f, 0.075f, 1.000f);
    guis->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.075f, 0.075f, 0.075f, 1.000f);

    guis->Colors[ImGuiCol_ChildBg] = ImVec4(0.075f, 0.075f, 0.075f, 1.000f);
    guis->Colors[ImGuiCol_PopupBg] = ImVec4(0.075f, 0.075f, 0.075f, 1.000f);

    guis->Colors[ImGuiCol_TitleBg] = ImVec4(0.109f, 0.136f, 0.137f, 1.000f);
    guis->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.164f, 0.346f, 0.357f, 1.000f);
    guis->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.094f, 0.179f, 0.184f, 1.000f);

    guis->Colors[ImGuiCol_Tab] = ImVec4(0.141f, 0.164f, 0.155f, 1.000f);
    guis->Colors[ImGuiCol_TabHovered] = ImVec4(0.419f, 0.473f, 0.451f, 0.710f);
    guis->Colors[ImGuiCol_TabActive] = ImVec4(0.334f, 0.617f, 0.746f, 0.847f);

    guis->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.239f, 0.228f, 0.363f, 0.408f);
    guis->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.465f, 0.574f, 0.632f, 0.847f);

    guis->Colors[ImGuiCol_Header] = ImVec4(0.259f, 0.373f, 0.383f, 1.000f);
    guis->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.159f, 0.270f, 0.279f, 1.000f);
    guis->Colors[ImGuiCol_HeaderActive] = ImVec4(0.191f, 0.368f, 0.384f, 1.000f);

    guis->Colors[ImGuiCol_Button] = ImVec4(0.094f, 0.094f, 0.094f, 1.000f);
    guis->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.263f, 0.421f, 0.435f, 0.894f);
    guis->Colors[ImGuiCol_ButtonActive] = ImVec4(0.232f, 0.487f, 0.510f, 0.702f);

    guis->Colors[ImGuiCol_FrameBg] = ImVec4(0.163f, 0.467f, 0.494f, 0.000f);
    guis->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.196f, 0.358f, 0.373f, 0.000f);
    guis->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.196f, 0.441f, 0.463f, 1.000f);

    guis->Colors[ImGuiCol_Separator] = ImVec4(0.341f, 0.494f, 0.507f, 1.000f);
    guis->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.399f, 0.841f, 0.881f, 0.729f);
    guis->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.399f, 0.841f, 0.881f, 0.729f);

    guis->Colors[ImGuiCol_CheckMark] = ImVec4(1.000f, 0.906f, 0.929f, 1.000f);

    guis->Colors[ImGuiCol_SliderGrab] = ImVec4(0.289f, 0.650f, 0.682f, 1.000f);
    guis->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.320f, 0.706f, 0.741f, 1.000f);

    guis->Colors[ImGuiCol_DockingPreview] = ImVec4(0.151f, 0.438f, 0.483f, 1.000f);
    guis->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.183f, 0.411f, 0.431f, 0.137f);

    guis->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.248f, 0.650f, 0.686f, 1.000f);
    guis->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.266f, 0.842f, 0.894f, 1.000f);
    guis->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.075f, 0.535f, 0.576f, 1.000f);

    guis->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.399f, 0.431f, 0.414f, 1.000f);
    guis->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.465f, 0.502f, 0.481f, 1.000f);
    guis->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.632f, 0.663f, 0.646f, 1.000f);

    guis->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.290f, 0.794f, 0.839f, 1.000f);

    guis->TabRounding = 1;
    guis->TabBorderSize = 1;

    guis->PopupRounding = 1;
    guis->PopupBorderSize = 1;

    guis->FrameRounding = 0;
    guis->FrameBorderSize = 1;

    guis->WindowTitleAlign = ImVec2(1.0f, 0.5f);
    guis->WindowMenuButtonPosition = 0;
    guis->ScrollbarRounding = 2;
}
void Editor::renderFrame(GLFWwindow* render)
{
    //
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
        imguiHud();
        ImGui::ShowDemoWindow();
    ImGui::EndFrame();

    //
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwGetFramebufferSize(render, &w, &h);
    glfwSwapBuffers(render);

    clearRenderFrame(); // clear back
}
void Editor::rendering()
{
    started = true;

    imguiHudStyle();

    glfwSetKeyCallback(render, keyboardCallback);

    glfwSetWindowUserPointer(render, this);
    //glfwSetWindowPosCallback(render, resizeRenderCallback);
    glfwSetFramebufferSizeCallback(render, resizeRenderCallback);
    glfwSwapInterval(0); // vertical sync 0/1

    glfwSetWindowSizeLimits(render, w, h, GLFW_DONT_CARE, GLFW_DONT_CARE);

    while (!glfwWindowShouldClose(render))
    {
        clearRenderFrame(); // clear back

        // rendering
        renderFrame(render);

        glfwPollEvents(); // events
    }
    closeRender();
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void Editor::openNextPopup(std::string next, bool clearPopup)
{
    nextPopup = true;
    this->clearPopup = clearPopup;

    backPopup = popup;
    popup = next;

    if (next == "Project list")
    {
        if (allProjectsList.size())     allProjectsList.clear();
        if (allProjectsPlatform.size()) allProjectsPlatform.clear();
    }
    else
    if (next == "Create New Project")
        project_architectureBuffer = 0;
}
void Editor::closePopup()
{
    openNextPopup("");
    ImGui::CloseCurrentPopup(); // close popup
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
bool Editor::testProjectPathName(std::string projectName)
{
    if (projectName != "")
    {
        bool result = true;
        for (size_t i = 0; i < projectName.length(); i++)
        {
            if ( projectName[i] == ' ' || (!isChar(projectName[i]) && !isInt(projectName[i])) )
            {
                result = false;
                break;
            }
        }
        return result;
    }
    else return false;
}
std::vector<std::string> Editor::createNewImportFile(std::string path, std::string name, std::string type, std::string import, bool newFile)
{
    std::vector<std::string> pathName = getFileName(path);
    std::vector<std::string> noType = noFileType(pathName[0]);
    std::string nameType = '.'+pathName[0].substr(atoi(noType[1].c_str()) + 1, pathName[0].size());
    //std::cout << "1. NameType: " << NameType << std::endl;
    //std::cout << "2. PathName: " << PathName[0] << std::endl;
    //std::cout << "3. NoType: " << NoType[0] << std::endl;

    std::vector<std::string> newPath = getNameNum(noType[0]);
    if (newPath[0] == "") // 1 symbol name fix
        newPath[1] = std::to_string(name.length());

    std::string newName = name.substr(0, atoi(newPath[1].c_str()));
    //std::cout << "NewName: " << NewName << std::endl;

    size_t i = 1;
    if (newFile) // if new
    {
        //std::cout << "NewFile ->> true" << std::endl;
        while (true)
        {
            newName = name.substr(0, atoi(newPath[1].c_str()));

            if (newName[newName.length() - 1] == ' ')
                newName += std::to_string(i);
            else
                newName += " " + std::to_string(i);

            name = newName;
            newName = path.substr(0, atoi(pathName[1].c_str())) + newName + nameType;
            //std::cout << ":: " << NewName << std::endl;

            if (!fileExist(newName))
            {
                path = newName;
                break;
            }
            else
                i++;
        }
    }
    else // open
    {
        if (fileExist(path.substr(0, atoi(pathName[1].c_str())) + noFileType(newName.substr(0, newName.length()))[0] + nameType))
        {
            std::cout << "::File exist: true" << std::endl;
            openNextPopup("Project Explorer File Exist");
            return { "", "" };
        }
        //else
        //    std::cout << "::File exist: false" << std::endl;
    }

    // --
    if (type == "object" && newFile)
        import = getFileRoot(import)+name+".lua";
    //else
    //    std::cout << ":Import: " << Import << std::endl;
    
    // NameType 1 dot fix
    {
        std::string buffer = "";
        size_t dotCounter = 0;
        for (size_t i = 0; i < nameType.length(); i++)
        {
            if (nameType[i] == '.')
            {
                if (dotCounter == 1)
                {
                    nameType = buffer;
                    break;
                }
                else
                    buffer += nameType[i];
                dotCounter++;
            }
            else
                buffer += nameType[i];
        }
    }
    // create
    createNewFile(path,
        {
            "-- Import file",
            "name = \""+name+nameType+"\"",
            "type = \""+type+"\"",
            "import = \""+import+"\""
        });
    return {path, name}; // return our path
}
bool Editor::createNewProject(std::string projectName)
{ // true = create new || false = dir exist
    // clear back
    project_states.clear();

    //
    project_root = engine_data[2]+project_name+"\\";
    project_import = project_root+"import\\";

    // is projects dir
    std::wstring path1 = std::wstring(project_root.begin(), project_root.end());
    if (!dirExist(engine_data[2]))
        CreateDirectory(std::wstring(engine_data[2].begin(), engine_data[2].end()).c_str(), NULL);

    // create project folder
    //std::cout << ProjectDir << std::endl;
    if (dirExist(this->project_root))
        return false;
    else
        CreateDirectory(path1.c_str(), NULL);
        
        CreateDirectory( (path1 + L"\\objects").c_str(), NULL );
        CreateDirectory( (path1 + L"\\scenes").c_str(), NULL );
            copyFileTo(engine_data[4]+"scenes\\main.les", project_root+"scenes\\");
            copyFileTo(engine_data[4]+"scenes\\main.lua", project_root+"scenes\\");
        CreateDirectory( (path1+L"\\Textures").c_str(), NULL );
            // TO:DO: create gui func button to create a templates ?
            // LE::CopyFileTo(EngineData[4]+"Entity.lua", ProjectDir+"Objects\\");
            copyFileTo(engine_data[4]+"objects\\camera.lua", project_root+"objects\\");
            copyFileTo(engine_data[4]+"objects\\object.lua", project_root+"objects\\");
        CreateDirectory( (path1+L"\\animations").c_str(), NULL );
        CreateDirectory( (path1+L"\\fonts").c_str(), NULL );
        CreateDirectory( (path1+L"\\shaders").c_str(), NULL );
        CreateDirectory( (path1+L"\\sounds").c_str(), NULL );

        CreateDirectory( (path1+L"\\import").c_str(), NULL );
            createNewImportFile(project_import+"camera.lua.import", "camera", "object", "objects\\\\camera.lua", false);
            createNewImportFile(project_import+"object.lua.import", "object", "object", "objects\\\\object.lua", false);
            createNewImportFile(project_import+"main.les.import", "main", "scene", "scenes\\\\main.les", false);

    // create main project files
    createNewFile(project_root+"project.lep",
        {
            "-- Lacuna Engine project configuration file\n",
            "engine_version = \""+engine_data[0]+"\""+"\n",
            "project_name         = \""+project_name+"\"",
            "project_architecture = \""+std::to_string(project_architectureBuffer)+"\"",
            "project_platform     = \""+project_platform+"\"",
        });

    // log
    l.push("i1", "Created a new project: ["+project_name+"], Path: ["+project_root+"]");
    return true;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// reqiaster c++ func
void Editor::registerEngineMethods(lua_State* l)
{
    luaTable(l, "le");
    // -- TO:DO MORE FUNC
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
std::vector<std::string> Editor::getLuaFileVars(std::string file, std::vector<std::string> searchVars)
{
    std::vector<State*> tempStates;
    pushState(file.c_str(), tempStates, false);

    std::vector<std::string> Result;
    for (size_t i = 0; i < searchVars.size(); i++)
    {
        Result.emplace_back( tempStates[0]->str(searchVars[i].c_str()) ); // TO:DO if load error
    }

    return Result;
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// push state to back in vector
void Editor::pushState(const char* FileName, std::vector<State*>& states, bool engineFunc)
{
    states.emplace_back(new State());
	lua_pushlightuserdata(states[states.size()-1]->getLuaState(), this);
    lua_setglobal(states[states.size()-1]->getLuaState(), luaEngineAccessor);

    if (engineFunc)
        registerEngineMethods(states[states.size()-1]->getLuaState());
    states[states.size()-1]->loadFile(FileName);
}
// open project init file
void Editor::useProjectScript(size_t StateID)
{
    std::string engineVersion = project_states[StateID]->str("EngineVersion"); // TO:DO if load error
    if (this->engine_data[0] != engineVersion)
        l.push("w", "Engine version != Project version"); // log
    
    std::string project_name         = project_states[StateID]->str("project_name");         // TO:DO if load error
    std::string project_architecture = project_states[StateID]->str("project_architecture"); // TO:DO if load error
    std::string project_platform     = project_states[StateID]->str("project_platform");     // TO:DO if load error

    this->project_name = project_name;
    this->project_architecture = std::atoi(project_architecture.c_str());
    this->project_platform = project_platform;
}
// open import file
void Editor::useImportScript(size_t StateId)
{
    std::string name   = importStates[StateId]->str("name");   // TO:DO if load error
    std::string type   = importStates[StateId]->str("type");   // TO:DO if load error
    std::string import = importStates[StateId]->str("import"); // TO:DO if load error

    if (!name.length() || !type.length() || !import.length())
    {
        l.push("e", "Unable to import file: "+ importStates[StateId]->fileName);
        return;
    }

    if (type == "object")
    {
        project_importFile.objects.emplace_back(Import::ImportFile(import, type, name));
    }
    else if (type == "scene")
    {
        project_importFile.scenes.emplace_back(Import::ImportFile(import, type, name));

        jsonFile f = getJSON(project_root+import);
        scene_list = f.getArray("objects");
        scene_manager.addScene(l, f.getName("name"));
    }
    else if (type == "scene script")
    {
        project_importFile.scenes.emplace_back(Import::ImportFile(import, type, name));
    }
    else if (type == "texture")
    {
        project_importFile.textures.emplace_back(Import::ImportFile(import, type, name));
    }
    else if (type == "font")
    {
        project_importFile.fonts.emplace_back(Import::ImportFile(import, type, name));
    }
    else if (type == "shader")
    {
        project_importFile.shaders.emplace_back(Import::ImportFile(import, type, name));
    }
    else if (type == "sound")
    {
        project_importFile.sounds.emplace_back(Import::ImportFile(import, type, name));
    }
}
// open dialog for lua file
std::vector<std::string> Editor::openLuaFileDialog(std::vector<State*>& states, bool clearStates, LPCWSTR filter, LPCWSTR initialDir)
{
    // --
    std::string path = openFileDialog(filter, initialDir);

    // -- read file
    if (path != "")
    {
        if (clearStates)
            project_states.clear();
        pushState(path.c_str(), states);
        return {"t", path };
    }
    else return { "f", path };
}
void Editor::openImportFile(std::string file)
{
    l.push("i2", "["+file+"]"); // log
    pushState(file.c_str(), importStates, false);
    useImportScript(importStates.size()-1);
}
void Editor::openImportFiles()
{
    //std::cout << ProjectDir << std::endl;
    std::vector<std::string> files = getFilesList(project_import, { "*.import" });

    for (size_t i = 0; i < files.size(); i++)
        openImportFile(files[i]);
}
bool Editor::openProject(std::vector<std::string> existProject)
{
    std::vector<std::string> open;
    // 0 - t/f
    // 1 - path

    if (existProject.size())
    {
        open = existProject;
        pushState(existProject[1].c_str(), project_states);
    }
    else
        // open and clear back states
        open = openLuaFileDialog(project_states, true, L"Lacuna Engine project (*.lep)\0*.lep\0", stringToWideString(engine_data[2]).c_str());
    // path fix
    if (true)
    {
        std::vector<std::string> path;
        std::string buffer;
        for (size_t i = 0; i < open[1].length(); i++)
        {
            buffer += open[1][i];
            if (open[1][i] == '\\')
            {
                path.emplace_back(buffer);
                buffer = "";
            }
            else
            if (open[1][i] == '.')
            {
                break;
            }
        }
        buffer = "";
        for (size_t i = 0; i < path.size(); i++)
        {
            buffer += path[i];
        }
        open[1] = buffer;
    }
    // --
    if (open[0] == "t")
    {
        //
        project_root = open[1];
        l.push("p", "=> project"); // log
        // clear back
        scene_manager.clearScenes();
        l.push("c", "[Clear Scene Manager]"); // log

        //
        project_importFile = Import();
        project_import = project_root+"import\\";
        openImportFiles();
        useProjectScript(0);

        l.push("i1", "Project opened: ["+project_name+"], Path: ["+open[1]+"]"); // log
        l.push("c", "");                                                        // log
        return true;
    }
    else
    {
        if (open[1] != "")
            l.push("w", "Unable to open project: Path: ["+open[1]+"]"); // log
        else
            l.push("i1", "Cancel project opening"); // log
        l.push("c", "");
        return false;
    }
}
void Editor::closeProject(bool openAllProjects)
{
    // TO:DO close project
    scene_manager.clearScenes();

    // --
    if (openAllProjects)
        openNextPopup("Project list");

    project_name = "~";

    project_root = "";
    project_import = "";

    for (size_t i = 0; i < project_states.size(); i++)
        project_states[i]->del();
    project_states.clear();
    for (size_t i = 0; i < importStates.size(); i++)
        importStates[i]->del();
    importStates.clear();

    // set null path
    fs::current_path(engine_data[1]);
}
// close process window by name
void CloseWindowByTitle(const std::wstring& windowTitle)
{
    HWND hWnd = FindWindowW(nullptr, windowTitle.c_str());
    if (hWnd != nullptr)
    {
        SendMessage(hWnd, WM_CLOSE, 0, 0);
    }
}
// process by title visible
bool IsWindowVisibleByTitle(std::wstring title)
{
    // Ищем окно с заданным названием титульника
    HWND hwnd = FindWindowW(NULL, title.c_str());
    if (hwnd == NULL) {
        // Если окно не найдено, возвращаем false
        return false;
    }

    // Получаем информацию об окне
    DWORD pid;
    DWORD tid = GetWindowThreadProcessId(hwnd, &pid);
    DWORD style = GetWindowLong(hwnd, GWL_STYLE);

    // Проверяем, показано ли окно на данный момент
    return ((style & WS_VISIBLE) != 0);
}
void CheckWindow(const std::wstring& windowTitle, bool& sceneStarted)
{
    std::thread thread([=, &sceneStarted]() {
        while (true)
        {
            HWND hwnd = FindWindow(nullptr, windowTitle.c_str());
            if (hwnd == nullptr)
            {
                sceneStarted = false;
                return;
            }

            // 100ms to next search
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        });

    thread.detach();
}
bool Editor::startProject()
{
    size_t scenes = scene_manager.getScenesSize();
    if (scenes)
    {
        LE::Scene& s = scene_manager.getCurrentScene();
        l.push("i1", "Scene: ["+s.name+"] ["+std::to_string(scene_manager.currentScene+1)+"/"+std::to_string(scenes)+"] is running");

        //S.BuildScene(L, ProjectDir, ProjectImport);

                printf("LuaJIT version: %s\n", LUAJIT_VERSION);
                /*
                State* Scene = new State();
                std::string json_str = "{\"name\":\"John\",\"age\":25,\"city\":\"city17\"}";

                Scene->json(json_str);
                Scene->PrintAll();
                Scene->Save("table.lua");
                */

                /*
                CreateObject("TestObj", R"(
                    {
	                    "age": 25,
	                    "city": "city17",
	                    "city2": "city28",
	                    "textures": [
		                    ["Textures/Player.png", "rgba_f:1,1,1,1"],
		                    ["Textures/Enemy.png", "rgba_f:0.5,0.5,0.5,1"],
		                    ["Textures/Bullet.png", "rgba_f:0,0,0,0.8"]
	                    ]
                    }
                 )");
                */

                //std::vector<std::string> lines = CommentsInLuaScript("script.lua");
                //for (const auto& line : lines) {
                //    std::cout << line;
                //}

                // создаём сцену ->> TO:DO: перенести при созлании нового проекта
                /*
                const char* filename = "scene.json";
                const char* json_string = R"(
                    {
	                    "name": "scene1",
	                    "objects": []
                    }
                )";
                bool result = CreateJSON(filename, json_string);
                if (!result) {
                    std::cerr << "Failed to create JSON file: " << filename << "\n";
                }
                */

                // Добавляем объект в сцену
                //AddObjectToScene("scene.json", "Player1", 580, 452, 24, 24, "Textures/Player.png", "rgba_f:1,1,1,1");
                //AddObjectToScene("scene.json", "Castle1", 612, 452, 24, 24, "Textures/Castle.png", "rgba_f:1,1,1,1");

                return false;
                
        // start game
        SECURITY_ATTRIBUTES sa;
        ZeroMemory(&sa, sizeof(sa));
        sa.nLength = sizeof(sa);
        sa.bInheritHandle = TRUE;

        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        std::string exePath = "Lacuna Engine.exe";
        std::string projectArgs = "G~" + engine_data[2] + project_name + "~F~1280~768";
        std::wstring cmdLine = L"\"" + stringToWideString(exePath) + L"\" 0 \"" + stringToWideString(projectArgs) + L"\"";

        if (!CreateProcess(stringToWideString(exePath).c_str(), &cmdLine[0], &sa, &sa, TRUE, 0, NULL, NULL, &si, &pi))
        {
            printf("CreateProcess failed (%d).\n", GetLastError());
            // TO:DO: to editor log
        }

        while (true)
        {
            bool v = IsWindowVisibleByTitle( stringToWideString(project_name) );
            if (v)
            {
                scene_started = true;
                CheckWindow(stringToWideString(project_name), scene_started);
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Wait until child process exits.
        //WaitForSingleObject(pi.hProcess, INFINITE);
        
        // Close process and thread handles. 
        //CloseHandle(pi.hProcess);
        //CloseHandle(pi.hThread);

        //
        return true;
    }
    else
    {
        scene_started = false;
        return false;
    }
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void Editor::imguiHud()
{
    // -- main menu bar
    guis->DisplaySafeAreaPadding = ImVec2(10, 8);
    guis->FramePadding = ImVec2(4, 8);
    ImGui::BeginMainMenuBar();
    ImGui::Text((project_name+" |").c_str());
    if (ImGui::BeginMenu("Project"))
    {
        if (menuItemImage("New", "newFile", "", true))
        {
            openNextPopup("Create New Project");
        }
        if (menuItemImage("Import", "openFolder", "", true))
        {
            openProject();
        }
        if (menuItemImage("Save", "saveFile", "", true, false))
        {

        }
        ImGui::Separator();
        if (menuItemImage("Project list", "newFiles", "", true))
        {
            openNextPopup("Project list");
        }
        if (menuItemImage("Settings", "settings2", "", true))
        {
            
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Close", NULL, false, true))
        {
            closeProject();
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Window"))
    {
        if (ImGui::MenuItem("Project explorer", NULL, show_projectExplorer, true))
        {
            show_projectExplorer ? ImGui::SetWindowFocus("Project explorer") : void();
            show_projectExplorer = !show_projectExplorer;
        }
        if (ImGui::MenuItem("Scene list", NULL, show_sceneList, true))
        {
            show_sceneList ? ImGui::SetWindowFocus("Scene list") : void();
            show_sceneList = !show_sceneList;
        }
        if (ImGui::MenuItem("Inspector", NULL, show_inspector, true))
        {
            show_inspector ? ImGui::SetWindowFocus("Inspector") : void();
            show_inspector = !show_inspector;
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Log", NULL, show_log, true))
        {
            show_log ? ImGui::SetWindowFocus("Log") : void();
            show_log = !show_log;
        }
        if (ImGui::MenuItem("Script output", NULL, show_scriptOutput, true))
        {
            show_scriptOutput ? ImGui::SetWindowFocus("Script output") : void();
            show_scriptOutput = !show_scriptOutput;
        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Settings"))
    {

    }
    ImGui::EndMainMenuBar();
    guis->DisplaySafeAreaPadding = ImVec2(4, 4);
    guis->FramePadding = ImVec2(5, 4);

    // -- main background space
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    guis->WindowRounding = 0.0f;
    guis->WindowPadding = ImVec2(0.0f, 0.0f);

    ImGui::Begin("##MainBackground", 0, mainBackgroundFlags);
        backgroundDockSpace = ImGui::GetID("BackgroundDockSpace");
        ImGui::DockSpace(backgroundDockSpace, ImVec2(0.0f, 0.0f));

        if (ImGui::BeginMenuBar())
        {
            guis->WindowPadding = ImVec2(6.0f, 6.0f);
            if (!scene_started)
            {
                if (menuItemImage("##Scene_Start", "start", "Start scene"))
                {
                    if( !startProject() ) l.push("i1", "No launch scene");
                }
            }
            else
            {
                if (menuItemImage("##Scene_Stop", "stop", "Stop scene"))
                {
                    scene_started = false;
                    //SceneManager.GetCurrentScene().UnbuildScene(L);
                    CloseWindowByTitle(stringToWideString(project_name)); // TO:DO: only if game started

                    l.push("i1", "Scene stopped");
                    l.push("c", "");
                }
            }
            if (menuItemImage("##Scene_Pause", "pause", "Pause scene"))
            {
                // ScenePaused = true; <<-- TO:DO
                std::cout << "Pause" << std::endl;
            }
            ImGui::EndMenuBar();
        }
    ImGui::End();
    // -- other windows

        // game render
        window_sceneView();

        // Image Editor TO:DO: test 1 editor
        if (!firstHudDraw)
        {
            imageEditors.emplace_back(ImageEditor("File 1"));
        }
        for (size_t i = 0; i < imageEditors.size(); i++)
        if (imageEditors[i].show)
        {
            window_imageEditor(imageEditors[i]);
        }
        // Text Editor
        window_textEditor("1");
        // Node Editor
        window_nodeEditor("1");

        // => focus to render
        if (!firstHudDraw)
            ImGui::SetWindowFocus("Scene View");

        // -- log
        if (show_log)
            window_log();

        // -- script output
        if (show_scriptOutput)
        {
            ImGui::Begin("Script output");
                so.Draw();
            ImGui::End();
        }

        // explorer
        if (show_projectExplorer)
            window_projectExplorer();

        // inspector
        if (show_inspector)
            window_inspector();

        // scene
        if (show_sceneList)
            window_sceneList();

    // -- 
    if (!firstHudDraw)
    {
        ImGuiID MainID_Right = ImGui::DockBuilderSplitNode(backgroundDockSpace, ImGuiDir_Right, 0.18f, NULL, &backgroundDockSpace);
        ImGuiID MainID_Bottom = ImGui::DockBuilderSplitNode(backgroundDockSpace, ImGuiDir_Down, 0.24f, NULL, &backgroundDockSpace);

        ImGui::DockBuilderDockWindow("Scene list", MainID_Right);
        ImGui::DockBuilderDockWindow("Log", MainID_Bottom);
        ImGui::DockBuilderDockWindow("Script output", MainID_Bottom);

        ImGuiID MainID_Central = ImGui::DockBuilderGetCentralNode(backgroundDockSpace)->ID;
        //ImGuiID ExplorerID = ImGui::DockBuilderGetNode(MainID_Central)->ID;

        ImGuiID MainID_Left = ImGui::DockBuilderSplitNode(MainID_Central, ImGuiDir_Left, 0.18f, NULL, &backgroundDockSpace);
        ImGui::DockBuilderDockWindow("Project explorer", MainID_Left);

        ImGuiID ExplorerID_Right = ImGui::DockBuilderSplitNode(MainID_Right, ImGuiDir_Down, 0.50f, NULL, &backgroundDockSpace);
        ImGui::DockBuilderDockWindow("Inspector", ExplorerID_Right);
        
        ImGui::DockBuilderFinish(backgroundDockSpace);

        firstHudDraw = true;
    }

    // -- pupup's
    popup_createNewProject();
    popup_projectExist();
    popup_projectList();
    popup_deleteProject();

    popup_explorerContext();
    popup_explorerAddContext();

    popup_fileExist();
    popup_deleteFile();

    // --
    if (popup != "" && nextPopup)
    {
        //std::cout << "BackPopup: \""+BackPopup+"\", Popup: \""+Popup+"\", ClearPopup: "<<ClearPopup << std::endl;
        ImGui::OpenPopup(popup.c_str());
        if (clearPopup)
            popup = "";
        clearPopup = false;
        nextPopup = false;
    }
}