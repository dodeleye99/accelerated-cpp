// small C++ program takes lines of text and counts the number of times each word occurs.
#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::max;
using std::string;
using std::ispunct;


// creates a blank-space string to be used for padding the output
string pad_str(string s, string::size_type pad_factor)
{
    if (pad_factor < s.size())
        return " ";

    return string(pad_factor - s.size() + 1, ' ');

}

int main()
{
    // declare string used to read user input into.
    string s;
    // store each word and associated counter
    map<string, int> counters; 

    // mark the length of maximum word for padding
    string::size_type maxlen = 0;

    cout << "Input any sequence of words, "
            "followed by end-of-file: " << endl;
    
    // read the input, keeping track of each word and how often we see it
    while (cin >> s) {

        // remove any punctiuation symbols surrounding the word
        while(!s.empty() && ispunct(s[0]))
        {
            s.erase(0);
        }
        while(!s.empty() && ispunct(s[s.size() - 1]))
        {
            s.erase(s.size() - 1);
        }

        if (!s.empty()) {
            maxlen = max(maxlen, s.size());
            // using the word as a key, increment the count of the word
            // (if the map does not yet have the key, it is created first with initial value 0)
            ++counters[s];
        }

    }
    cout << endl;

    // First check whether no words were entered.
    if (counters.empty()) {
        cout << "You must enter a sequence of words. "
                "Please try again." << endl;
        // End the program, returning non-zero value to indicate failure.
        return 1;
    }

    cout << "Number of times each distinct word appears: " << endl;
    // write the words and associated counts
    // (note that the iterator will automatically iterate over the key-value pairs in key-alphabetical order)
    for (map<string, int>::const_iterator it = counters.begin();
        it != counters.end(); ++it) {
            // format: <word> <pad> <count>
            cout << it->first << pad_str(it->first, maxlen) << it->second << endl;
        }
    return 0;
}
