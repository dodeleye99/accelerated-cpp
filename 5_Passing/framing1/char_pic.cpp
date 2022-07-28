#include <algorithm>
#include <string>
#include <vector>

#include "char_pic.h"

using std::max;
using std::string;
using std::vector;


// calculates the width of the longest "line" in a given character picture, represented by a vector of strings.
string::size_type width(const vector<string>& v)
{
    string::size_type maxlen = 0;

    for(vector<string>::const_iterator iter = v.begin(); iter != v.end(); ++iter) {
        maxlen = max(maxlen, (*iter).size());
    }
    return maxlen;
}

// outputs a "framed" picture out of a given character picture.
vector<string> frame(const vector<string>& v)
{
    vector<string> ret;
    string::size_type maxlen = width(v);
    string border(maxlen + 4, '*');

    // write the top border
    ret.push_back(border);

    // write each interior row, bordered by an asterix and a space
    for(vector<string>::const_iterator iter = v.begin(); iter != v.end(); ++iter) {
        ret.push_back("* " + *iter + string(maxlen - (*iter).size(), ' ') + " *");
    }

    // write the bottom border
    ret.push_back(border);
    return ret;
}

// concatenate two character pictures vertically
vector<string> vcat(const vector<string>& top,
                    const vector<string>& bottom) 
{
    // copy the top picture
    vector<string> ret = top;

    // copy entire bottom picture at the end of the copy of the top picture
    ret.insert(ret.end(), bottom.begin(), bottom.end());

    return ret;
    // THIS IS EQUIVALENT TO:
    // for(vector<string>::const_iterator iter = bottom.begin(); iter != bottom.end(); ++iter)
    //     ret.push_back(*iter);
}

// concatenate two character pictures horizontally
vector<string> hcat(const vector<string>& left, const vector<string>& right)
{
    vector<string> ret;

    // add 1 to leave a space between pictures
    string::size_type width1 = width(left) + 1;

    // indices to look at elements from left and right respectively
    vector<string>::size_type i = 0, j = 0;

    // continue until we've seen all the rows from both pictures
    while (i != left.size() || j != right.size()) {
        // construct new string to hold characters from both pictures
        string s;

        // copy a row from the left-hand side, if there is one
        if (i != left.size())
            s = left[i++];  // i++ means "increment i, returning original value of i"
        
        // pad to full width
        s += string(width1 - s.size(), ' ');
 
        if (j != right.size())
            s += right[j++];

        // copy a row from the right-hand side, if there is one
        ret.push_back(s);
    }
    return ret;
}

// i++ means "increment i, returning original value of i"
// ++i means increment i, returning the new value of i"

// (i, j] = j - i  | | | | |i| | | |j|
