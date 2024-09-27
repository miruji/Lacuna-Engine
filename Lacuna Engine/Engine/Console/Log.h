#pragma once
#include <iostream>

#include <filesystem>
namespace fs = std::filesystem;

#include "../File/dirExist.h"
#include "../File/fileExist.h"
#include "../File/newDirectory.h"
#include "../File/newFile.h"
#include "../File/getRootPath.h"

#include "ConsoleTime.h"
#include "ConsoleStyle.h"

#include <ImGUI/imgui.h>
#include "ImGUI/imgui_internal.h"
#include "../Graphics/Texture.h"

namespace LE
{
	class Log
	{
	private:
		std::string getFileName(); // to .log file

	public:
		// --
		struct Line
		{
			size_t x = 1;
			std::string beginData;
			std::string time, type, data;
			
			Line(std::string time, std::string type, std::string data)
			{
				this->time = time;
				this->type = type;
				this->data = time+data;
				beginData = data;
			};
			void anotherOne()
			{
				x++;
				data = time+beginData+" x"+std::to_string(x);
			}
		};
		std::vector<Line> list;
		bool updateScrollY = true; // scroll to down y
		bool updateScrollYSecond = false;

		// --
		Log();
		~Log();
		void saveFile(); // save new log file
		void push(std::string type, std::string data);

		void logLine(std::vector<Texture>& guii, const char* label, std::string guiIconName, size_t i, bool enabled = true);
		size_t logLineRightClick  = 0; // 0 - no | more +1
		bool logLineFirst = true;
		void draw(std::vector<Texture>& guii, ImGuiStyle* guis); // ImGui window draw
	};
}