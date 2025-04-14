#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

// this function should expect that `expression` has already been
// validated and thus throw no exceptions
double parse_number(const std::string &expression);
std::string add_string(std::string &s, std::string &s2);
bool is_valid_double(const std::string& s);

#endif // __CALCULATOR_HPP
