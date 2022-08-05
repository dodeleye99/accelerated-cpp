#include <string>

#include "pad_str.h"

using std::string;


// creates a blank-space string to be used for padding the output
string pad_str(string s, string::size_type pad_factor /* = maxlen*/)
{
    if (pad_factor < s.size())
        return " ";

    return string(pad_factor - s.size() + 1, ' ');

}
