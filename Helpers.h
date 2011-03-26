#include <string>
#include <cstdio>

inline std::string toString(const int& toConvert)
{
    char buffer[8];
    std::sprintf(buffer, "%d", toConvert);
    return buffer;
}