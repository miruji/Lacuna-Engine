#include "Game.h"
using namespace LE;

Game::Game(std::string name, size_t w, size_t h, std::string root, std::vector<std::string> engine_data) : Window(name, w, h)
{
    this->name = name;

    this->root = root; // TO:DO: if no slash in root path (add func)
    this->root_import = root+"import\\";

    this->engine_data = engine_data;
}
Game::Game() : Window()
{
}
Game::~Game()
{
}
void Game::keyboardCallback(GLFWwindow* render, int key, int scancode, int action, int mods)
{
    Game* e = static_cast<Game*>(glfwGetWindowUserPointer(render));

    //
    if (key == GLFW_KEY_F4 && action == GLFW_PRESS)
        glfwSetWindowShouldClose(render, GL_TRUE);
    else
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS)
        e->showWindowInfo = !e->showWindowInfo;
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
void Game::clearRenderFrame()
{
    glClearColor(rgba_to_float(59, 117, 99, 255));      // bg color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // color & depth
}
void Game::resizeRenderCallback(GLFWwindow* render, int w, int h)
{
    Game* g = static_cast<Game*>(glfwGetWindowUserPointer(render));

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
    g->renderFrame(render);
}
void Game::imguiHudStyle()
{
    // imgui styles
    guis = &ImGui::GetStyle();

    guis->Colors[ImGuiCol_Border] = ImVec4(0.595f, 0.781f, 0.661f, 0.388f);

    guis->Colors[ImGuiCol_WindowBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.497f);
    guis->Colors[ImGuiCol_ChildBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.497f);
    guis->Colors[ImGuiCol_PopupBg] = ImVec4(0.000f, 0.000f, 0.000f, 0.497f);

    guis->Colors[ImGuiCol_Button] = ImVec4(0.000f, 0.000f, 0.000f, 0.000f);
    guis->Colors[ImGuiCol_ButtonHovered] = ImVec4(1.000f, 1.000f, 1.000f, 0.177f);
    guis->Colors[ImGuiCol_ButtonActive] = ImVec4(1.000f, 1.000f, 1.000f, 0.215f);
}
void Game::renderFrame(GLFWwindow* Render)
{
    //
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    if (scene_started == false)
        startProject();

    ImGui::NewFrame();
        imguiHud();
    ImGui::EndFrame();

    //
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwGetFramebufferSize(Render, &w, &h);
    glfwSwapBuffers(Render);

    clearRenderFrame(); // clear back
}
void Game::rendering()
{
    started = true;

    imguiHudStyle();

    glfwSetKeyCallback(render, keyboardCallback);

    glfwSetWindowUserPointer(render, this);
    //glfwSetWindowPosCallback(render, resizeRenderCallback);
    glfwSetFramebufferSizeCallback(render, resizeRenderCallback);
    resizeRenderCallback(render, w, h);
    glfwSwapInterval(0); // vertical sync 0/1

    glfwSetWindowSizeLimits(render, w, h, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetWindowAttrib(render, GLFW_RESIZABLE, GLFW_FALSE); // no resizable

    while (!glfwWindowShouldClose(render))
    {
        // clear back
        clearRenderFrame();

        //
        glEnable(GL_TEXTURE_2D);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // rendering
        renderFrame(render);

        glfwPollEvents(); // events
    }
    closeRender();
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// reqiaster c++ func
void Game::registerEngineMethods(lua_State* l)
{
    luaTable(l, "le");
    // -- TO:DO: more func ?
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
// push state to back in vector
void Game::pushState(const char* fileName, std::vector<State*>& states, bool engineFunc)
{
    states.emplace_back(new State());
    lua_pushlightuserdata(states[states.size() - 1]->getLuaState(), this);
    lua_setglobal(states[states.size() - 1]->getLuaState(), luaEngineAccessor);

    if (engineFunc)
        registerEngineMethods(states[states.size() - 1]->getLuaState());
    states[states.size() - 1]->loadFile(fileName);
}
// open import file
void Game::useImportScript(size_t StateID)
{
    if (StateID == 0)
    {
        this->name = importStates[StateID]->str("project_name"); // TO:DO if load error
    }
    else
    {
        //
        std::string name   = importStates[StateID]->str("name");   // TO:DO if load error
        std::string type   = importStates[StateID]->str("type");   // TO:DO if load error
        std::string import = importStates[StateID]->str("import"); // TO:DO if load error

        if (!name.length() || !type.length() || !import.length())
        {
            l.push("e", "Unable to import file: " + importStates[StateID]->fileName);
            return;
        }

        if (type == "object")
        {
            project_import.objects.emplace_back(Import::ImportFile(import, type, name));
        }
        else if (type == "scene")
        {
            project_import.scenes.emplace_back(Import::ImportFile(import, type, name));

            jsonFile F = getJSON(root+import);
            scene_manager.addScene(l, F.getName("name"));
        }
        else if (type == "scene script")
        {
            project_import.scenes.emplace_back(Import::ImportFile(import, type, name));
        }
        else if (type == "texture")
        {
            project_import.textures.emplace_back(Import::ImportFile(import, type, name));
        }
        else if (type == "font")
        {
            project_import.fonts.emplace_back(Import::ImportFile(import, type, name));
        }
        else if (type == "shader")
        {
            project_import.shaders.emplace_back(Import::ImportFile(import, type, name));
        }
        else if (type == "sound")
        {
            project_import.sounds.emplace_back(Import::ImportFile(import, type, name));
        }
        //
    }
}
void Game::openImportFile(std::string file)
{
    l.push("i2", "[" + file + "]"); // log
    pushState(file.c_str(), importStates, false);
    useImportScript(importStates.size() - 1);
}
void Game::openImportFiles()
{
    std::vector<std::string> Files = getFilesList(root_import, { "*.import" });

    for (size_t i = 0; i < Files.size(); i++)
        openImportFile(Files[i]);
}
bool Game::startProject()
{
    size_t scenes = scene_manager.getScenesSize();
    if (scenes)
    {
        LE::Scene& s = scene_manager.getCurrentScene();

        State* StartProject = new State();

        scene_started = true;
        l.push("i1", "Scene: ["+s.name+"] ["+std::to_string(scene_manager.currentScene+1)+"/"+std::to_string(scenes)+"] is running");

        s.buildScene(l, root, project_import);

        guis->WindowBorderSize = 0;
        guis->WindowPadding = ImVec2(0, 0);
        guis->ItemSpacing   = ImVec2(0, 0);

        if (glfwGetWindowAttrib(render, GLFW_VISIBLE) == GLFW_FALSE) {
            glfwShowWindow(render);
        }

        glfwSetWindowTitle(render, name.c_str());

        //
        return true;
    }
    else
    {
        openImportFile(root+"project.lep");
        openImportFiles();

        scene_started = false;
        return false;
    }
}
// = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
void Game::imguiHud()
{
    Scene& s = scene_manager.getCurrentScene();

    // opengl scene frame
    if (scene_started && s.cCurrent != -1)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, s.fbo);

        glBindTexture(GL_TEXTURE_2D, s.fboTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
        glBindTexture(GL_TEXTURE_2D, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, s.fboTexture, 0);

        // background Clear
        // TO:DO: no draw / repeat draw / color draw
        glBegin(GL_QUADS);
        glColor4f(rgba_to_float(59, 117, 99, 255));
            glVertex2f(0, 0);
            glVertex2f(0, h);
            glVertex2f(w, h);
            glVertex2f(w, 0);
        glEnd();

        s.states[0]->func("update"); // lua update
        // TO:DO: in update and init no use draw func ?
        s.states[0]->func("draw"); // lua draw
        // TO:DO: if you use draw func in lua then add to main lua draw stream

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            l.push("e", "Couldn't create frame buffer");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // draw scene frame
        glBindTexture(GL_TEXTURE_2D, s.fboTexture);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1); glVertex2f(0, 0);
            glTexCoord2f(0, 0); glVertex2f(0, h);
            glTexCoord2f(1, 0); glVertex2f(w, h);
            glTexCoord2f(1, 1); glVertex2f(w, 0);
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }

    // gui
    if (showWindowInfo)
    {
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        if (!firstHudDraw)
        {
            ImGui::SetNextWindowSize(ImVec2(340, 50));
            ImGui::SetNextWindowPos(ImVec2(8, 8));
        }
        ImGui::Begin("##scene_info", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
                                           ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse |
                                           ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
                                           ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoDocking);
        // -- render
        if (scene_started && scene_manager.currentScene != -1)
        {
        // frame info
            const auto& currentScene = scene_manager.getScene(scene_manager.currentScene);
            ImGui::Text("Current scene: num: [%d], name: [%s]", scene_manager.currentScene, currentScene.name.c_str());
            ImGui::Text("Current camera: num: [%d], x: %d, y: %d", s.cCurrent, -static_cast<int>(s.c[s.cCurrent].x), -static_cast<int>(s.c[s.cCurrent].y));

            if (ImGui::IsWindowHovered())
            {
                if (mouse_x >= 0)
                    mouse_x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
                if (mouse_y >= 0)
                    mouse_y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;
            }

            ImGui::Text("Application average: %.3f, ms/frame: %.1f FPS",
                1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
        }
        ImGui::End();
        ImGui::PopStyleColor(2);
    }
}