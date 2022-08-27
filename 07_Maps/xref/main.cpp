// takes lines of text and shows outputs a cross-reference list for each word that appears.
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "pad_str.h"
#include "remove_punct.h"
#include "split.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::istream;
using std::map;
using std::max;
using std::string;
using std::vector;


// mark the length of maximum word for padding
// (defined in "global" scope since both main() and xref() need to accesss it)
string::size_type maxlen;


// find all the lines that refer to each word in the input
map<string, vector<int> > xref(istream& in, vector<string> find_words(const string&) = split)
{
    // specify string used to store the current line read.
    string line;
    // record the current line number in order to reference it.
    int line_number = 0;
    // create a map to hold line references for each word.
    map<string, vector<int> > ret;
        
    maxlen = 0;

    // read the next line
    while (getline(in, line)) {

        ++line_number;

        /**
         * Break the input line into words using a given word-extraction function.
         * If xref() is called, passing in the input stream but WITHOUT passing any argument for the find_words parameter, 
         *  then as a default the split() function will be used to extract the words.
         **/
        vector<string> words = find_words(line);

        // for each word read, remember the (current) line it occurs on by storing a reference to it.
        for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
            // (add 2 to max padding length because the cross-reference list will surround 
            //  each word with quotation marks)

            // create new string with all surrounding punctuation symbols removed.
            string s = remove_punct(*it);
            maxlen = max(maxlen, s.size() + 2); 
            ret[s].push_back(line_number);
        }

    }
    return ret;

}

int main()
{
    // prompt the user
    cout << "Input lines of text, "
            "followed by end-of-file, " 
            "to generate a cross-reference list:" << endl;

    // call xref using split by default
    map<string, vector<int> > refs = xref(cin);

    // First check whether no text were entered.
    if (refs.empty()) {
        cout << "You must enter lines of text. "
                "Please try again." << endl;
        // End the program, returning non-zero value to indicate failure.
        return 1;
    }

    // begin to generate the cross-reference list
    cout << endl;
    cout << "=====================" << endl;
    cout << "Cross-reference list:" << endl;
    cout << "=====================" << endl;

    // write the results
    for (map<string, vector<int> >::const_iterator it = refs.begin();
         it != refs.end(); ++it){

        // write the word (with padding)
        cout << "\'" << it->first << "\'" << pad_str(it->first, maxlen) << "occurs on line(s): ";

        // followed by one or more line numbers
        vector<int>::const_iterator line_it = it->second.begin();
        cout << *line_it; // write the first line number

        ++line_it;

        // then write any remaining line numbers
        while (line_it != it->second.end()) {
            cout << ", " << *line_it;
            ++line_it;
        }
        // write a new line to separate each word from the next
        cout << endl;
    }

    return 0;
}
