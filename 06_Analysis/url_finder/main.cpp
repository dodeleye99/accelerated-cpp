#include <iostream>
#include <string>
#include <vector>


#include "find_urls.h"

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
    vector<string> urls;

    cout << "Input lines of text to extract any URLs found in each:\n" << endl;

    // read and split each line of input (until EOF recieved)
    while (getline(cin, s)) {

        vector<string> v = find_urls(s);
        urls.insert(urls.end(), v.begin(), v.end());
    }

    cout << "\n\nURLs found: " << endl;

    // output each line
    for(vector<string>::const_iterator iter = urls.begin(); iter != urls.end(); ++iter) {
        cout << *iter << endl;
    }
}