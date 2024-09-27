#include "ConsoleTime.h"

// get current date, format is YYYY-MM-DD
std::string LE::GetDate()
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm tstruct = *std::localtime(&now_c);

    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d", &tstruct);

    return buf;
}
// get curre t time, format is HH:MM:SS
std::string LE::GetTime(std::string DEL)
{
    using namespace std::chrono;
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);
    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, ("%H"+DEL+"%M"+DEL+"%S").c_str()); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}