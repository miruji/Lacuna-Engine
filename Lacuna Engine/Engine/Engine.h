#pragma once
#include "Window.h"
#include "Editor/Editor.h"
#include "Game/Game.h"

#include "Lua/State.h"
#include "Console/Console.h"

#include <math.h>

#include "../Func/wideStringConvert.h"
#include "../Func/splitString.h"
#include "../File/getFileReplaceAll.h"

namespace LE
{
	// --
	class Engine
	{
		private:
			bool engine_started = false; // begin engine

			std::string start_projectPath = "?";
			std::string start_resolutionMode = "false";
			size_t start_w = 1280;
			size_t start_h = 768;

			// lua states
			std::vector<State*> engine_states;
			void pushInitState(const char* fileName, std::vector<State*>& states);

			void useEngineScript(size_t stateID);

			// lua c++ func
			void registerEngineMethods(lua_State* l);

			static int le_log(lua_State* l);
			static int le_editor(lua_State* l);
			static int le_game(lua_State* l);
			std::vector<size_t> resizeStartResolution(bool mode, size_t w, size_t h);

			// nearest width & height
			int nearestWidth(size_t value);
			int nearestHeight(size_t value);

			// engine dirs
			std::string engine_dir          = ""; // le/
			std::string engine_projectsDir  = ""; // le/projects/
			std::string engine_dataDir      = ""; // le/data/
			std::string engine_templatesDir = ""; // le/data/templates/

			// enigne settings
			std::string engine_version = "";
				
				size_t engine_mode = 0; // 0 - Editor | 1 - Game |
				LE::Editor* engine_editor;
				LE::Game* engine_game;

				//std::vector<LE::Window> EngineWindows;

			std::vector<std::string> engine_windowResolutions = {
				"4096x2160", "3840x2160",
				"3440x1440", "2560x2048",
				"2560x1600", "2560x1440",
				"2560x1080", "2048x1536",
				"2048x1080", "1920x1200",
				"1920x1080", "1680x1050",
				"1600x1200", "1600x900",
				"1440x1080", "1440x960",
				"1440x900", "1400x1050",
				"1366x768", "1280x1024",
				"1280x960", "1280x854",
				"1280x800", "1280x768",
				"1280x720", "1152x864",
				"1152x768", "1024x768",
				"1024x600", "1024x576",
				"854x480", "800x600",
				"800x480", "768x576",
				"640x480", "480x320",
				"384x288", "352x288",
				"320x240", "320x200"
			};

		public:
			// log
			LE::Log l;
			LE::ScriptOutput so;

			Engine();
			~Engine();

			void save();
			void start(char start_engineMode = 'E', std::string start_rojectPath = "?", std::string start_resolutionMode = "false", size_t start_w = 1280, size_t start_h = 768);
			void stop();
	};
}