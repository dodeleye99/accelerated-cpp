/**
 * A program that takes lines of sentences as input, 
 * outputting for each their words as they are entered, line by line.
 **/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

#include <string>
using std::string;

#include "String_list.h"
#include "split.h"


int main()
{
    // will hold each sentence inputted
    string s;

    // prompt the user
    cout << "Input sentences to split into words as they are entered. To stop, input end-of-file " << endl;

    // read and split each line of input as they are entered (until EOF recieved)
    while (getline(cin, s)) {

        // use our String_list class to create a list to hold the words in each sentence read
        String_list sl = split(s);
        
        cout << endl;
        
        // output each line
        for(String_list::iterator iter = sl.begin(); iter != sl.end(); ++iter) {
            cout << *iter << endl;
        }
        cout << endl;
    }
    
    return 0;
}
