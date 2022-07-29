#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

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
    
    // define a simpler name representing a string iterator
    typedef string::const_iterator iter;

    vector<string> ret;

    iter i = str.begin();

    while (i != str.end()) {
        
        // ignore leading blanks: return first iterator in range [i, str.end()) that does not point to a space
        i = find_if(i, str.end(), not_space);

        // ^ Equivalent to:
        //// while (i != str.end() && space(*i))
        ////    ++i;
        
        // find end of next word: the first iterator in range [i, str.end()) that points to a space
        iter j = find_if(i, str.end(), space);

        // ^ Equivalent to:
        //// j = i;
        //// while (j != str.end() && not_space(*j))
        ////    ++j;
       
        // copy the characters in [i, j) (unless no more words exist in string)
        if (i != str.end())
            ret.push_back(string(i, j));
        i = j;
    }
    return ret;
}

/**
 * === ALGORITHMS ===
 * find_if(iter1, iter2, f) - searches a container bounded by iterators [iter1, iter2) and returns the iterator pointing to the 
 *  first value that passes the predcate f. If not found, then iter2 is returned.
 **/