// a program that copies the contents of a file to one or more other files.
#include <fstream>
using std::ifstream;
using std::ofstream;

#include <iostream>
using std::cerr;
using std::cout;
using std::endl;

#include <string>
using std::getline;
using std::string;


// Copy the contents of a given input file to a file with the given name
// (If the output file already exists, it will be overwritten)
void copy_file(ifstream& infile, const char* out)
{   
    // Form a stream for writting text to the given file.
    ofstream outfile(out);

    // Used to hold the text of the current line read
    string s;

    // Write each line of text to the output file.
    while (getline(infile, s)) {
        outfile << s << endl;
    }

    // Clear stream due to end-of-file reached, allowing it to be read again for another copy.
    infile.clear();

    // restart the file reading position, enabling it to be read from the beginning to perform any further copies.
    infile.seekg(0);
}


int main(int argc, char** argv)
{   
    // The program needs at least one argument passed to do anything
    if (argc > 1) {

        // The first argument represents the input file to copy from
        ifstream in(argv[1]);

        // Check whether the input file can be opened
        if(in) {
            
            // Any further arguments are files to copy the input file to
            if(argc > 2) {
                size_t i = 2;
                // Copy the input file to all the files passed. 
                while (in && i < argc) {
                    copy_file(in, argv[i]);
                    cout << "The file \'" << argv[1] << "\' has been copied to \'" << argv[i] << "\'." << endl;
                    ++i;
                }      
            } else {
                // If there were no more arguments, then it is copied to a file named "out" by default
                const char* out = "out";
                copy_file(in, out);

                cout << "The file \'" << argv[1] << "\' has been copied to \'" << out << "\'.";
            }    
        } else {
            // Mark as an error if input file does not exist
            cerr << "cannot open file \'" << argv[1] << "\'" << endl;
            return 1;
        }
    }
    // If no arguments passed, immediately end the program with a note to uses.
    else {
        cout << "No input file argument entered. Ending program..." << endl;
    }

    return 0;
}

/**
 * ifstream:  represents a stream used only to read text from files.
 * outstream: represents a stream used only to write text to files.
 * 
 **/