#include "replaceAll.h"

void LE::replaceAll(std::string& S, std::string const& ToReplace, std::string const& ReplaceWith)
{
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(S.size());

    while (true) {
        prevPos = pos;
        pos = S.find(ToReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(S, prevPos, pos-prevPos);
        buf += ReplaceWith;
        pos += ToReplace.size();
    }

    buf.append(S, prevPos, S.size()-prevPos);
    S.swap(buf);
}