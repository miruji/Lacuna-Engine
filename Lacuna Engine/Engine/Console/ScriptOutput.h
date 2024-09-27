#pragma once
#include <iostream>
#include "../File/DirExist.h"
#include "../File/FileExist.h"
#include "../File/NewDirectory.h"
#include "../File/NewFile.h"
#include "../File/GetRootPath.h"

#include "ConsoleTime.h"
#include "ConsoleStyle.h"

namespace LE
{
	class ScriptOutput
	{
	private:


	public:
		// --
		struct Line
		{
			char Type; std::string Data;
			Line(char Type, std::string Data)
			{
				this->Type = Type;
				this->Data = Data;
			};
		};
		std::vector<Line> List;

		// --
		ScriptOutput();
		~ScriptOutput();
		void Push(char Type, std::string Data);
		void Draw(); // ImGui window draw
	};
}