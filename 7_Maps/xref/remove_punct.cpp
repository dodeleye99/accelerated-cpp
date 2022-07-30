#include <cctype>
#include <string>

#include "remove_punct.h"

using std::ispunct;
using std::string;


// returns a new string with all punctiuation symbols surrounding the original string removed
string remove_punct(string s)
{   
    while(!s.empty() && ispunct(s[0]))
    {
        s.erase(0);
    }
    while(!s.empty() && ispunct(s[s.size() - 1]))
    {
        s.erase(s.size() - 1);
    }

    return s;
}