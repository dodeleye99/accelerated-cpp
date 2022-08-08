#include <algorithm>
using std::find_if;

#include <string>
using std::string;

#include "split.h"
#include "String_list.h"

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


// splits a sentence (words separated by space) into a string of vectors
String_list split(const std::string& str){
    
    // define a mnemonic for the string's (read-only) iterator type
    typedef string::const_iterator iter;
    // define a String_list object that will eventually hold all the words split from the sentence
    String_list ret;

    // start at the beginning of the string
    iter i = str.begin();

    // reading through string until its end
    while (i != str.end()) {
        
        // ignore leading blanks: return first iterator in range [i, str.end()) that does not point to a space
        i = find_if(i, str.end(), detail::not_space);

        // find end of next word: the first iterator in range [i, str.end()) that points to a space
        iter j = find_if(i, str.end(), detail::space);

        // add the string of characters in [i, j) to the string list.
        if (i != str.end())
            ret.push_back(string(i, j));

        // set i to be equal to j, to prepare to read the remaining parts of string.
        i = j;
    }
    return ret;
}