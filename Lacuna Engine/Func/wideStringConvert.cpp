#include "wideStringConvert.h"

// utf8 ->> utf16
std::wstring LE::stringToWideString(const std::string string)
{
    if (string.empty())
    {
        return L"";
    }

    const auto size_needed = MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), nullptr, 0);
    if (size_needed <= 0)
    {
        throw std::runtime_error("MultiByteToWideChar() failed: " + std::to_string(size_needed));
    }

    std::wstring result(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, &string.at(0), (int)string.size(), &result.at(0), size_needed);
    return result;
}
// utf16 ->> utf8
std::string LE::wideStringToString(const std::wstring wide_string)
{
    if (wide_string.empty())
    {
        return "";
    }

    const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
    if (size_needed <= 0)
    {
        throw std::runtime_error("WideCharToMultiByte() failed: " + std::to_string(size_needed));
    }

    std::string result(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
    return result;
}
//
LPWSTR LE::convertWideString(const std::string& instr)
{
    // Assumes std::string is encoded in the current Windows ANSI codepage
    int bufferlen = ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), NULL, 0);
    if (bufferlen == 0)
    {
        // Something went wrong. Perhaps, check GetLastError() and log.
        return 0;
    }

    // Allocate new LPWSTR - must deallocate it later
    LPWSTR widestr = new WCHAR[bufferlen+1];
    ::MultiByteToWideChar(CP_ACP, 0, instr.c_str(), instr.size(), widestr, bufferlen);

    // Ensure wide string is null terminated
    widestr[bufferlen] = 0;

    // Do something with widestr
    return widestr;
    //delete[] widestr;
}
std::string LE::tcharToString(const TCHAR* tcharString)
{
    // Определяем размер буфера, необходимого для хранения преобразованной строки
    int bufferSize = WideCharToMultiByte(CP_UTF8, 0, tcharString, -1, nullptr, 0, nullptr, nullptr);

    // Выделяем буфер под преобразованную строку
    std::string result(bufferSize, '\0');

    // Преобразуем строку в UTF-8
    WideCharToMultiByte(CP_UTF8, 0, tcharString, -1, &result[0], bufferSize, nullptr, nullptr);

    // Удаляем завершающий нулевой символ
    result.pop_back();
    return result;
}