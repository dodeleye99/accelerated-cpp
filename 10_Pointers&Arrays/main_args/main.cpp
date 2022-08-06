// a program that outputs the command line arguments passed to the program
#include <iostream>
using std::cout;
using std::endl;


int main(int argc, char** argv)
{   
    // give acknowledgement to the user the running of the program, outputting also its name
    cout << "Running " << argv[0] << "..." << endl;

    // if there are command-line arguments, write them
    if (argc > 1) {
        // write the first argument
        cout << argv[1];

        // write each remaining argument with a space before it
        for (int i = 2; i != argc; ++i) { 
            // argv[i] is a char*
            cout << " " << argv[i];
        }
    }
    cout << endl;
    return 0;
}

/**
 * 'argv' is a pointer to the initial element of an array of character pointers, one for each argument given.
 * 'argc' is the number of pointers in the array of which argv points to the inital element.
 * 
 * Note that 'argv' will always have an initial element equal to the name of the executable program.
 * 
 * E.g. if the output is named "rumme", and we execute the program by
 * 
 *              ./runme Hello, World!
 * 
 * then "Hello," and "World!" will be passed as the arguments, and
 *              argc = 3 and argv = ["./runme", "Hello,", "World!"]
 * 
 * This particular program will then output
 *                  Running ./runme...
 *                  Hello, World!
 **/
