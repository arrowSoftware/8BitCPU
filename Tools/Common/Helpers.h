#ifndef __Helpers_HPP__
#define __Helpers_HPP__

#include <string>

extern bool is_number(const std::string& s);
extern int parseNumber(std::string number);
extern bool ichar_equals(char a, char b);
extern bool isEqual(const std::string& a, const std::string& b);
extern std::string trim(const std::string& str, const std::string& whitespace = " \t");
extern std::string reduce(const std::string& str,
                          const std::string& fill = " ",
                          const std::string& whitespace = " \t");

#endif // __Helpers_HPP__
