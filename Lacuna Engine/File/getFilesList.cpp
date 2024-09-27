#include "getFilesList.h"

std::vector<std::string> LE::getFilesList(std::string filePath, std::vector<std::string> extension)
{
	std::vector<std::string> result;
	// --
    WIN32_FIND_DATA fileInfo;
    HANDLE hFind;
    std::string fullPath;
        
    for (size_t i = 0; i < extension.size(); i++) // multiload
    {
        fullPath = filePath + extension[i];
        // --
        std::wstring stemp = std::wstring(fullPath.begin(), fullPath.end());
        LPCWSTR sw = stemp.c_str();
        hFind = FindFirstFile(sw, &fileInfo);

        if (hFind != INVALID_HANDLE_VALUE){
            result.push_back( filePath+wideStringToString(std::wstring(fileInfo.cFileName)) );
            while (FindNextFile(hFind, &fileInfo) != 0){
                result.push_back( filePath+wideStringToString(std::wstring(fileInfo.cFileName)) );
            }
        }
    }
    // --
	return result;
}