#pragma once
#include <GL/glew.h> // glewInit()
#define  GLFW_INCLUDE_GLU
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>

#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_glfw.h>
#include <ImGUI/imgui_impl_opengl3.h>

#include <SOIL/SOIL.h>

// --
#include <iostream>

#include "Lua/LuaLoad.h"
#include "Console/Console.h"

#include "Import.h"

// --
#include "FreeImage/FreeImage.h"
#include "../File/getFilesList.h"

#include "Graphics/GUI/GUI.h"
#include "../Func/splitString.h"

#include <filesystem>
namespace fs = std::filesystem;

namespace LE
{
	class Window
	{
	protected:
		// --
		GLFWwindow* render; // Main stream Render

		ImGuiStyle* guis = NULL;   // gui style
		std::vector<Texture> guii; // gui icons

		// new gui
		bool menuItemImage(std::string label, std::string guiiName, const char* desc = "", bool verticalMenu = false, bool enabled = true);
		bool treeNodeImage(std::string label, std::string guiiName, size_t& click, bool selected = false, bool addButton = false, bool arrow = true, size_t doubleClick = 0, std::string dragAndDrop = "");

	private:
		static void renderError(int code, const char* desc);
		static void renderResize(GLFWwindow* render, int newWidth, int newHeight);

	public:

		void loadGUIIcons();

		//
		LE::Log l;
		void mergeLog(LE::Log& l2);
		LE::ScriptOutput so;
		void mergeScriptOutput(LE::ScriptOutput& so2);

		std::string name = "Noname";
		float x = NULL, y = NULL;
		int w = NULL, h = NULL;

		Window(std::string name, size_t w, size_t h);
		Window();
		~Window();

		bool started = false;
		void createRender(const bool maximize, const bool visible);
		void closeRender();
		void closeRender2();
	};
}