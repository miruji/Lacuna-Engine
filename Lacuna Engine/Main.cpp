#include <iostream>
#include "Engine/Engine.h"
#include "Func/splitString.h"
#include "Func/wideStringConvert.h"

#include <fstream>
#include <conio.h>
#include <Windows.h>

std::string getLastErrorMessage()
{
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0)
    {
        return std::string(); // нет ошибки
    }

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, nullptr);

    std::string message(messageBuffer, size);

    // освобождаем выделенный буфер
    LocalFree(messageBuffer);

    // удаляем пробелы и отступы в конце сообщения
    size_t endpos = message.find_last_not_of(" \t\r\n");
    if (endpos != std::string::npos)
    {
        message = message.substr(0, endpos + 1);
    }

    return message;
}

#include <shellapi.h>
#include <iostream>

bool isUserAdmin()
{
    BOOL fAdmin = FALSE;
    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    PSID AdministratorsGroup;
    if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup)) {
        if (!CheckTokenMembership(NULL, AdministratorsGroup, &fAdmin)) {
            fAdmin = FALSE;
        }
        FreeSid(AdministratorsGroup);
    }
    return fAdmin == TRUE;
}

LE::Engine e;
fs::path enginePath = fs::current_path();
void saveExit()
{
    fs::current_path(enginePath); // set null path
    e.save();                     // save on end
}
BOOL WINAPI handlerRoutine(DWORD eventCode)
{
    switch (eventCode)
    {
    case CTRL_CLOSE_EVENT:
    case CTRL_LOGOFF_EVENT:
    case CTRL_SHUTDOWN_EVENT:
        saveExit();
        return FALSE;
        break;
    }

    return TRUE;
}
int wmain(int argc, wchar_t* argv[])
{
    if (argc < 2 || wcscmp(argv[1], L"1") == 0)
    {
        HWND hWnd = GetConsoleWindow();
        ShowWindow(hWnd, SW_HIDE);
    }
    system("title Lacuna Engine");
    //
    {
        // admin rights
        if (!isUserAdmin())
        {
            SHELLEXECUTEINFO sei = { sizeof(sei) };
            sei.lpVerb = L"runas";     // rights verb
            sei.lpFile = argv[0];      // exe
            sei.nShow = SW_NORMAL;     // show normal

            // argv
            std::wstring cmdLine;
            for (int i = 1; i < argc; i++) {
                cmdLine += argv[i];
                cmdLine += L" ";
            }

            //std::wcout << cmdLine << std::endl;
            //system("pause");
            sei.lpParameters = cmdLine.c_str(); // add argv line

            if (!ShellExecuteEx(&sei)) {
                e.l.push("e", "When starting the program with administrator rights: "+getLastErrorMessage());

                saveExit();
                return 1;
            }
        }
        else
        {
            // console settings
            HWND hWindowConsole = GetConsoleWindow(); RECT r;
            GetWindowRect(GetConsoleWindow(), &r); //stores the console's current dimensions
            MoveWindow(hWindowConsole, r.left, r.top, 1280, 480, TRUE);

            // engine start
            std::vector<std::string> argv_split;
            if (argc >= 3)
            {
                std::string argv_str;
                for (int i = 2; i < argc; i++)
                    argv_str += LE::wideStringToString(argv[i]) + " ";

                argv_split = LE::splitString(argv_str, '~');
            }
            if (argv_split.size()) 
            {
                char start_engineMode = 'E';
                if (argv_split.size() >= 1) start_engineMode = argv_split[0][0];

                std::string start_projectPath = "?";
                if (argv_split.size() >= 2) start_projectPath = argv_split[1];

                std::string start_resolutionMode = "false";
                if (argv_split.size() >= 3)
                {
                    if (argv_split[2][0] == 'T')
                        start_resolutionMode = "true";
                    else
                        start_resolutionMode = "false";
                }

                size_t start_w = 1280;
                if (argv_split.size() >= 4) start_w = atoi(argv_split[3].c_str());
                size_t start_h = 768;
                if (argv_split.size() >= 5) start_h = atoi(argv_split[4].c_str());

                e.start(start_engineMode, start_projectPath, start_resolutionMode, start_w, start_h);
            }
            else e.start(); // basic start

            SetConsoleCtrlHandler(handlerRoutine, TRUE);
            //_getch(); // it's a normal code ->> no system("pause")
            saveExit();
        }
    }
    return 0;
}