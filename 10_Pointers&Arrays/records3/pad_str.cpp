#include <string>

#include "pad_str.h"

using std::string;


// creates a blank-space string to be used for padding the output
string pad_str(string::size_type s_size, string::size_type pad_factor /* = maxlen*/)
{
    if (pad_factor < s_size)
        return " ";

    return string(pad_factor - s_size + 1, ' ');

}
string pad_str(string s, string::size_type pad_factor){
    return pad_str(s.size(), pad_factor);
}
string pad_str(string s, string pad_s){
    return pad_str(s.size(), pad_s.size());
}
string pad_str(string::size_type s_sz, string pad_s){
    return pad_str(s_sz, pad_s.size());
}
string pad_str(string pad_s){
    return pad_str(0, pad_s);
}
string pad_str(string::size_type pad_factor){
    return pad_str(0, pad_factor);
}

// // creates a blank-space string to be used for padding the output
// string pad_str(string s, string::size_type pad_factor /* = maxlen*/)
// {
//     if (pad_factor < s.size())
//         return " ";

//     return string(pad_factor - s.size() + 1, ' ');

// }
