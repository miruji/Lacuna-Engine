#pragma once
#include "../Window.h"
#include <string.h>

#include "../Lua/LuaMacro.h"

#include "../Game/SceneManager.h"

namespace LE
{
	class Game : public LE::Window
	{
	private:
		std::string name; // ~ = none

		std::string root;        // ? = none
		std::string root_import; //

		// render
		int mouse_x = 0, mouse_y = 0;

		void imguiHud();
		bool firstHudDraw = false;
		bool showWindowInfo = false;

		// import
		void registerEngineMethods(lua_State* l);
		void pushState(const char* fileName, std::vector<State*>& states, bool engineFunc);

		Import project_import;
		std::vector<State*> importStates;
		void useProjectScript(size_t stateID); // open project init file
		void useImportScript(size_t stateID);  // open import file

		void openImportFile(std::string file);
		void openImportFiles();

		// game/others
		bool startProject();

		SceneManager scene_manager;
		bool scene_started = false; // 0/1 - t/f

		// engine
		std::vector<std::string> engine_data;
		// 0 - EngineVersion
		// 1 - EngineDir
		// 2 - EngineProjectsDir
		// 3 - EngineDataDir

	public:
		Game(std::string name, size_t w, size_t h, std::string root, std::vector<std::string> engineData);
		Game();
		~Game();

		void rendering();
		void imguiHudStyle();
		static void resizeRenderCallback(GLFWwindow* render, int w, int h);
		static void keyboardCallback(GLFWwindow* render, int key, int scancode, int action, int mods);
		void clearRenderFrame();
		void renderFrame(GLFWwindow* render);
	};
}