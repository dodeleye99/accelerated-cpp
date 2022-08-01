#ifndef GUARD_split_h
#define GUARD_split_h

#include <vector>
#include <string>


/**
 * Since the functions within are only split() function's "helpers", not used by the main part of the program accessing
 * this header file, obscure it by placing it within a namespace labelled "detail".
 **/
namespace detail
{
    bool space(char c)
    {
        return isspace(c);
    }

    bool not_space(char c)
    {
        return !isspace(c);
    }
}


/**
 * ------------------------------------------------------------------------------
 * This function template represents a family of functions which splits a string
 *  with respect to the spaces found within it, and writes each split part to an
 *  (assumed but not strictly necessary) output iterator.
 * ------------------------------------------------------------------------------
 * The 'Out' type-parameter: represents an output (i.e. write-only) iterator,
 *  which points to a single value of some sequence of elements at a time, 
 *  which can be reassigned but not read.
 **/
template <class Out>
void split(const std::string& str, Out os) {

    // define a mnemonic for the string's (read-only) iterator type
    typedef std::string::const_iterator iter;

    // start at the beginning of the string
    iter i = str.begin();

    // reading through string until its end
    while (i != str.end()) {

        // ignore leading blanks: return first iterator in range [i, str.end()) that does not point to a space
        i = find_if(i, str.end(), detail::not_space);

        // find end of next word: the first iterator in range [i, str.end()) that points to a space
        iter j = find_if(i, str.end(), detail::space);

        // copy (write) the characters in [i, j) to the iterator
        if (i != str.end())
            *os++ = std::string(i, j);

        // set i to be equal to j, to prepare to read the remaining parts of string.
        i = j;
    }
}

std::vector<std::string> split(const std::string& str);

#endif