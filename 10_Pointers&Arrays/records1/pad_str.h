#ifndef GUARD_pad_str_h
#define GUARD_pad_str_h

#include <string>

/**
 * ===================================
 * Example scenaio for using pad_str()
 * ===================================
 * Consider the following columns of text written as output
 * =====================
 * very-long-name grade1
 * name           grade2
 * =====================
 * How does one know how much blank space does one need to write grade2 
 * after 'name' such that it is perfectly alligned with grade1?
 * 
 * Calling pad_str(name, very-long-name) will give the required string of blank space.
 * 
 * The size of any of the two names may also be entered instead.
 *
 * If short-name doesn't exist (an empty string), one can find the position of the next
 * column by calling any of
 *    pad_str(very-long-name)
 *    pad_str(0, very-long-name)
 *    pad_str("", very-long-name).
 **/
std::string pad_str(std::string::size_type, std::string::size_type);

std::string pad_str(std::string, std::string::size_type);
std::string pad_str(std::string, std::string);
std::string pad_str(std::string::size_type, std::string);
std::string pad_str(std::string);
std::string pad_str(std::string::size_type);


#endif