#include <algorithm>
#include <cctype>
#include <iterator>
#include <string>

using std::back_inserter;
using std::isspace;
using std::remove_copy_if;
using std::string;


bool space(char c)
{
    return isspace(c);
}

/**
 * Recieves a string and returns a new one w
 * with all white space removed.
 **/
string trim(const string& str)
{
    typedef string::const_iterator iter;
    string ret;

    remove_copy_if(str.begin(), str.end(), back_inserter(ret), space);

    return ret;
}