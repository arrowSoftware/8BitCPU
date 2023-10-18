#include "Helpers.h"

#include <algorithm>
#include <cctype>
#include <string>

bool ichar_equals(char a, char b)
{
    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
}

bool isEqual(const std::string& a, const std::string& b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), ichar_equals);
}
