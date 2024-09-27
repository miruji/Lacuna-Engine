#include "Editor.h"

// show any file
void LE::Editor::explorer_showInFolder()
{
	std::string p = project_root+explorer_type+"s\\";
	l.push("i1", "Show file in folder: ["+p+"]");
	ShellExecute(NULL, NULL, stringToWideString(p).c_str(), NULL, NULL, SW_SHOWNORMAL);
}