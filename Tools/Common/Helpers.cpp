#include "Helpers.h"

#include <algorithm>
#include <cctype>
#include <string>

bool is_number(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int parseNumber(std::string number) {
    if (number.substr(0,2) == "0x") {
        return std::stoi(number.substr(2, number.length()), nullptr, 16);
    } else if (number.substr(0, 2) == "0o") {
        return std::stoi(number.substr(2, number.length()), nullptr, 8);
    } else if (number[number.length()-1] == 'd') {
        return std::stoi(number.substr(0, number.length()-1), nullptr, 10);
    } else if (number[number.length()-1] == 'b') {
        return std::stoi(number.substr(0, number.length()-1), nullptr, 2);
    } else if (!is_number(number)) {
        return -1;
    } else {
        return std::stoi(number, nullptr, 10);
    }

    return -1;
}

bool ichar_equals(char a, char b) {
    return std::tolower(static_cast<unsigned char>(a)) == std::tolower(static_cast<unsigned char>(b));
}

bool isEqual(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(), ichar_equals);
}

std::string trim(const std::string& str, const std::string& whitespace) {
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos) {
        return ""; // no content
    }

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::string reduce(const std::string& str,
                   const std::string& fill,
                   const std::string& whitespace) {
    std::string result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos) {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}
