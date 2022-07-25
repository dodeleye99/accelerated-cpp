// simple C++ program that takes a sentence as input and outputs each of its words line by line.
#include <iostream>
#include <string>
#include <vector>  

#include "split.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;
using std::vector;

int main()
{
    // will hold each sentence inputted
    string s;

    cout << "Input a sentence to split into words: " << endl;

    // read and split each line of input (until EOF recieved)
    while (getline(cin, s)) {
        // use our split function to split the sentence into a vector of strings.
        vector<string> v = split(s);
        cout << endl;
        
        // output each line
        for(vector<string>::const_iterator iter = v.begin(); iter != v.end(); ++iter) {
            cout << *iter << endl;
        }

        cout << endl;
    }
    
    // ALTERNATIVELY:
    // while (getline(cin, s)) {
    //     vector<string> v = split(s);

    //     for(vector<string>::size_type i = 0; i != v.size(); ++i) {
    //         cout << v[i] << endl;
    //     }
    // }

    // EQUIVALENT TO:
    // while (cin >> s) {
    //     cout << s << endl;
    // }
    
    return 0;
}
// getline(istream, string): reads a whole line of text, storing it in a given string once the end of the line is reached.
// const_iterator: a read-only iterator, which allows for reading of the values it points to, but not modification of the values.