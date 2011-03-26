#include <string>
#include <cstdio>
#include <boost/foreach.hpp>

#define foreach BOOST_FOREACH
#define foreach_r BOOST_REVERSE_FOREACH

inline std::string toString(const int& toConvert)
{
    char buffer[8];
    std::sprintf(buffer, "%d", toConvert);
    return buffer;
}