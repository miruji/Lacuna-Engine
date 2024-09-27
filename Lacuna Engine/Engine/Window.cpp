#include "Window.h"
using namespace LE;

Window::Window(std::string name, size_t w, size_t h)
    : name(name), x(0), y(0), w(w), h(h)
{
}
Window::Window()
{
}
Window::~Window()
{
    closeRender2();
}
void Window::loadGUIIcons()
{
    l.push("i1", "Loading textures: ");

    const std::vector<std::string> filesList = getFilesList("data/icons/", { "*.bmp","*.png","*.jpg","*.dds" });
    std::vector<std::string> toLog;

    for (const auto& filename : filesList)
    {
        const std::vector<std::string> GUIIcons_Result = loadTextures(guii, { filename }, "Icon");
        toLog = splitString(GUIIcons_Result[0], '|');
        l.push(toLog[0], toLog[1]);
    }

    l.push("c", "");
}
void Window::renderError(int Code, const char* Desc)
{
    fputs(Desc, stderr);
}
void Window::createRender(const bool maximize, const bool visible)
{
    //
    if (!glewInit())
    {
        l.push("e", "GLEW not init");
        exit(-1);
    }
    if (!glfwInit())
    {
        l.push("e", "GLFW not init");
        exit(-1);
    }

    glfwSetErrorCallback(renderError);
    //
    if (visible == false) glfwWindowHint(GLFW_VISIBLE, false);
    render = glfwCreateWindow(w, h, name.c_str(), NULL, NULL);
    if (maximize)
    {
        // for games
        // 1 method
        /*
        GLFWmonitor* Monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* VideoMode = glfwGetVideoMode(Monitor);

        glfwWindowHint(GLFW_RED_BITS, VideoMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, VideoMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, VideoMode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, VideoMode->refreshRate);

        Render = glfwCreateWindow(Width, Height, Name.c_str(), Monitor, NULL);
        */
        // 2 method
        glfwMaximizeWindow(render);
        // 3 method
        //::ShowWindow(glfwGetWin32Window(Render), SW_MAXIMIZE);
    }
    if (render == NULL)
    {
        glfwTerminate();
        exit(-1);
    }
    else // next create
    {
        // set window icon
        {
            GLFWimage icons[1];
            icons[0].pixels = SOIL_load_image("Lacuna Engine 256x256.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
            glfwSetWindowIcon(render, 1, icons);
            SOIL_free_image_data(icons[0].pixels);
        }

        // context
        glfwMakeContextCurrent(render);

        // shader
        const char* glsl_version = "#version 130";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // = GUI init
        // setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.IniFilename = NULL; // .ini file

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

        //ImGui_ImplGlfw_Init(Render, true);

        // log start info
        l.push("i1", std::format("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION))) );
        l.push("i1", std::format("OpenGL Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR))) );
        l.push("i1", std::format("OpenGL Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))) );
        l.push("i1", std::format("OpenGL Shading Language Version: {}", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION))) );
        l.push("c", "");

        ImGui_ImplGlfw_InitForOpenGL(render, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
    }
    //
}
void Window::closeRender()
{
    // Shutdown 
    if (started)
    {
        closeRender2();

        l.push("i1", "Window: ["+name+"]: Render Closed");
        started = false;
    }
}
void Window::closeRender2()
{
    if (started)
    {
        // Shutdown 
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(render);
        render = nullptr; // Added for safety

        started = false;
    }
}
// ===========================================================================
bool Window::menuItemImage(std::string label, std::string guiiName, const char* desc, bool verticalMenu, bool enabled)
{
    return LE::menuItemImage(guii, label.c_str(), guiiName, desc, verticalMenu, enabled);
}
bool Window::treeNodeImage(std::string label, std::string guiiName, size_t& click, bool selected, bool addButton, bool arrow, size_t doubleClick, std::string dragAndDrop)
{
    return LE::treeNodeImage(guii, label, guiiName, click, selected, addButton, arrow, doubleClick, dragAndDrop);
}
// ===========================================================================
void Window::mergeLog(LE::Log& l2)
{
    for (size_t i = 0; i < l.list.size(); i++)
        l2.list.emplace_back(l.list[i]);
}
void Window::mergeScriptOutput(LE::ScriptOutput& so2)
{
    for (size_t i = 0; i < so.List.size(); i++)
        so2.List.emplace_back(so.List[i]);
}