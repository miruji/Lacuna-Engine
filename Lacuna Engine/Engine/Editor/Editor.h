#pragma once
#include "../Window.h"

#include <windows.h>
#include <wtsapi32.h>
#include <userenv.h>
#pragma comment(lib, "wtsapi32.lib")
#pragma comment(lib, "userenv.lib")

#include <thread>
#include <string.h>

#include "../Lua/LuaLoad.h"
#include <algorithm>
#include <regex>

#include "../Lua/json.h"

#include <filesystem>
namespace fs = std::filesystem;

#include <math.h>

#include "../File/dirExist.h"
#include "../File/createNewFile.h"
#include "../File/getFileName.h";
#include "../File/getFileRoot.h";
#include "../File/noFileType.h";
#include "../File/getNameNum.h";
#include "../File/getFolderList.h"
#include "../File/openFileDialog.h"
#include "../File/copyFileTo.h"

#include "../Editor/ImageEditor/ImageEditor.h"
#include "../Editor/TextEditor/TextEditor.h"
#include "../Editor/NodeEditor/NodeEditor.h"

#include "../Game/SceneManager.h"

namespace LE
{
	class Editor : public LE::Window
	{
	private:
		// render
		int mouse_x = 0, mouse_y = 0;

		std::string explorer_name = "";
		std::string explorer_type = "";

		std::string properties_name = "Empty";
		std::string properties_type = "~";

		// --
		void pushState(const char* fileName, std::vector<State*>& states, bool engineFunc = true);
			// lua c++ func
			void registerEngineMethods(lua_State* l);

		// === editor ===
		bool show_projectExplorer = true;
		bool show_inspector = true;
		bool show_sceneList = true;
		bool show_log = true;
		bool show_scriptOutput = true;

		ImGuiID backgroundDockSpace;

		void window_sceneView();

		void window_projectExplorer();
		void window_inspector();
		void window_sceneList();
		void window_log();

		void window_textEditor(std::string name);
		std::vector<TextEditor> textEditors;
		void window_imageEditor(ImageEditor& ie);
		std::vector<ImageEditor> imageEditors;
		void window_nodeEditor(std::string name);
		std::vector<NodeEditor> nodeEditors;

			// TO:DO: test drag and drop imgui
			//int ObjectSelected = -1;
			std::vector<cJSON*> scene_list;

		// === popup func ===
		std::string popup = "Project list";
		std::string backPopup = "";
		bool nextPopup = true;
		bool clearPopup = false;
		void openNextPopup(std::string next, bool clearPopup = false);
		void closePopup();
			
			void popup_projectList();
			void popup_createNewProject();
			void popup_projectExist();
			void popup_deleteProject();

			void popup_explorerContext();
			void popup_explorerAddContext();

			void popup_fileExist();
			void popup_deleteFile();

		// === utility func ===
		// (using explorer/properties window)
			
			// show any file folder
			void explorer_showInFolder();
			// rename any file
			void explorer_rename();
			// delete any file
			void explorer_delete();
			// remove any file
			void explorer_remove();

		//
		size_t project_architectureBuffer = 0;
		size_t project_architecture = 0;
			// 0 = none
			// 1 = x86
			// 2 = x64
			// 3 = x86/x64
		std::string project_platform = "Windows";

		std::string project_name = "~";

		std::string project_root = "";
		std::string project_import = "";

		bool testProjectPathName(std::string projectName);
		std::vector<std::string> createNewImportFile(std::string path, std::string name, std::string type, std::string import, bool newFile);
		bool createNewProject(std::string projectName);

		bool startProject();

		// --
		std::vector<State*> project_states;
		std::vector<State*> importStates;
		void useProjectScript(size_t stateID); // open project init file
		void useImportScript(size_t stateID);  // open import file

		std::vector<std::string> getLuaFileVars(std::string file, std::vector<std::string> searchVars);

		std::vector<std::string> openLuaFileDialog(std::vector<State*>& states, bool clearStates = false, LPCWSTR filter = L"Lua script (*.lua)\0*.lua\0", LPCWSTR initialDir = 0);
		bool openProject(std::vector<std::string> existProject = {});
		void closeProject(bool openAllProjects = true);
			Import project_importFile;
			void openImportFile(std::string file);
			void openImportFiles();

		void imguiHud();
		bool firstHudDraw = false;

		// engine
		std::vector<std::string> engine_data;
		// 0 - engine_version
		// 1 - engine_dir
		// 2 - engine_projectsDir
		// 3 - engine_dataDir
		// 4 - engine_templatesDir
		std::vector<std::string> allProjectsList;
		std::vector<size_t> allProjectsPlatform;
		std::string allProjectsDelete = "";

		// game/others
		SceneManager scene_manager;
		bool scene_started = false; // 0/1 - t/f

		// --
		ImGuiWindowFlags mainBackgroundFlags =
			ImGuiWindowFlags_MenuBar |              // menu bar
			ImGuiWindowFlags_NoDocking |            // no window docking
			ImGuiWindowFlags_NoResize |             // no window resize
			ImGuiWindowFlags_NoMove |               // no window move
			ImGuiWindowFlags_NoTitleBar |           // no window title bar
			ImGuiWindowFlags_NoCollapse |           // no minimize window
			ImGuiWindowFlags_NoScrollbar |          // no scroll bar
			ImGuiWindowFlags_NoScrollWithMouse |    // no scroll with mouse
			ImGuiWindowFlags_NoBackground |         // no background
			ImGuiWindowFlags_NoNavFocus |           // ?
			ImGuiWindowFlags_NoBringToFrontOnFocus; // background focus

	public:
		Editor(std::string name, size_t w, size_t h, std::vector<std::string> engine_data);
		Editor();
		~Editor();

		void rendering();
		void imguiHudStyle();
		static void resizeRenderCallback(GLFWwindow* render, int w, int h);
		static void keyboardCallback(GLFWwindow* render, int key, int scancode, int action, int mods);
		void clearRenderFrame();
		void renderFrame(GLFWwindow* render);
	};
}