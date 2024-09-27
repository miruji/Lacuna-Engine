#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>

#include <cJSON/cJSON.h>

#include "../File/FileExist.h"

namespace LE
{
    class jsonFile
    {
    private:
        cJSON* createObject(const std::vector<std::string>& Values);

    public:
        bool Created = true;
        std::string FilePath;

        jsonFile(const std::string& FilePath);
        jsonFile() { Created = false; }
        ~jsonFile();

        bool checkExistence(const char* Array, const char* CheckName);
        int getCount(const char* Array);
        bool addObjectTo(const std::string& To, const std::vector<std::string>& Values);

        cJSON* getData(const std::string& FilePath);
        std::string getName(const std::string& Name);
        std::vector<cJSON*> getArray(const std::string& Name);
    };
    std::string freadAll(FILE* file);
    bool createJSON(const std::string& FilePath, const std::string& Data);
    jsonFile getJSON(const std::string& FilePath, std::string Data = "");
}