// a program that outputs the contents of one or more files.
#include <fstream>
using std::ifstream;

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;
using std::ostream;

#include <string>
using std::getline;
using std::string;


// Reads the contents of a file, writting it to a given output stream
void read_file(ifstream& in, ostream& out)
{   
    // Used to hold the text of the current line read
    string s;

    // Write each line of text to the output stream.
    while (getline(in, s)) {
        out << s << endl;
    }
}

int main(int argc, char** argv)
{   
    // record the number of files that were unable to be read.
    int fail_count = 0;

    // The program needs at least one argument passed to actually do something
    if (argc > 1) {

        // for each file in the input list
        for (int i = 1; i < argc; ++i) {

            // prepare to read the file.
            ifstream in(argv[i]);

            // if it exists, output its contents
            if (in) {
                read_file(in, cout);
            } 
            // if the file does not exist (or if it cannot be read for some reason), generatre an error message
            else {
                cerr << "cannot open file \'" << argv[i] << "\'" << endl;
                ++fail_count;
            }
            cout << endl;
        }
    }
    // If no arguments passed, immediately end the program with a note to uses.
    else {
        cout << "No input file argument entered. Ending program..." << endl;
    }

    // return the number of unreadable files, to help determine how successful the program was.
    return fail_count;
}