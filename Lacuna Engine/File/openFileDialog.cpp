#include "openFileDialog.h"

// open file dialog
std::string LE::openFileDialog(LPCWSTR Filter, LPCWSTR InitialDir)
{
    // --
    OPENFILENAME ofn;
    wchar_t w_syFile[MAX_PATH + 1] = { 0 };

    ZeroMemory(&ofn, sizeof(OPENFILENAME));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = w_syFile;
    ofn.lpstrFile[0] = '\0';

    ofn.nMaxFile = 2048;
    ofn.nMaxFileTitle = 2048;

    ofn.lpstrFilter = Filter;
    ofn.nFilterIndex = 0;

    if (InitialDir != 0)
        ofn.lpstrInitialDir = InitialDir; //

    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    GetOpenFileName(&ofn);

    return wideStringToString(ofn.lpstrFile);
}