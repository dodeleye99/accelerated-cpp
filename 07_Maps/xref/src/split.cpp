#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include "split.h"

using std::find_if;
using std::isspace;
using std::string;
using std::vector;

bool space(char c)
{
    return isspace(c);
}

bool not_space(char c)
{
    return !isspace(c);
}

// splits a sentence (words separated by space) into a string of vectors
vector<string> split(const string& str) {
    
    typedef string::const_iterator iter;
    vector<string> ret;

    iter i = str.begin();

    while (i != str.end()) {
        
        // ignore leading blanks: return first iterator in range [i, str.end()) that does not point to a space
        i = find_if(i, str.end(), not_space);
        
        // find end of next word: the first iterator in range [i, str.end()) that points to a space
        iter j = find_if(i, str.end(), space);
       
        // copy the characters in [i, j)
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}