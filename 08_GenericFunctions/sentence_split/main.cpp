#include <iostream>
#include <iterator>
#include <string>

#include "split.h"

using std::cin;
using std::cout;
using std::endl;
using std::ostream_iterator;
using std::getline;
using std::string;

int main()
{
    // declare a string that will hold the current line of text inputted.
    string s;

    // prompt the user.
    cout << "Input a line of text to have each of its words written line by line. "
         << "To finally terminate, input end-of-file:\n" << endl;

    while (getline(cin, s)) {
        cout << endl;
        // split the string, writting the separated parts to the standard output stream, each on a separate line.
        split(s, ostream_iterator<string>(cout, "\n"));
        cout << endl;
    }
    return 0;
}
/**
 * ostream_iterator<T>(s, c): represents an output iterator that writes objects of type T to an output stream s.
 * after every write, a sequence of characters represented by the char pointer c is also written to the stream,
 * acting as a delimiter (used to mark divisions between each written object).
 **/