// program for framing lines of text
#include <iostream>
#include <string>
#include <vector>

#include "char_pic.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


int main()
{
    // vector to hold each line of text inputted
    vector<string> v;
    // string each line of text will be read into
    string s;

    // prompt user;
    cout << "Input lines of text to be framed, followed by end-of-file:" << endl;

    // read each line of input
    while (getline(cin, s)) {
        v.push_back(s);
    }
    cin.clear();

    // frame the lines of text
    vector<string> f = frame(v);

    // output the framed 'picture' formed by the vector
    for(vector<string>::const_iterator iter = f.begin(); iter != f.end(); ++iter) {
        cout << *iter << endl;
    }

    return 0;
}