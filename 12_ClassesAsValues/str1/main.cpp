// A Str class demo
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "Str.h"

#include <string>
using std::string;


int main(int argc, char** argv)
{   
    // Initialise a new Str object filled with '=' characters, 30 in number - to represent a divider line.
    const Str line(30, '=');

    // === PART 1: Outputting command arguments, each character on a separate line. ===
    
    // Output divider line
    cout << line << endl;

    // Declare a new Str object (default initialised as an empty Str).
    Str s;

    // Concatnate command arguments (in reverse order - see below)
    for(size_t i = argc; i != 0; --i) {

        /**
         * Let s hold the command arguments in a "semi-symmetric" form:
         * <arg1> <arg2> ... <argN> <argN> ... <arg2> <arg1>
         * 
         * For example, if argv = {""./runme", "Hello", "World""}
         * 
         * Then
         * s = ""./runme Hello World World Hello ./runme"
         * 
         * == NOTE ==
         * One cannot concatenate two string literals. But one may be concatenated with a Str,
         * since Str has an associated convertion operator to convert a const char* to a Str.
         * So we need to enssure that Str object concatenation is intendet here, by adding brackets 
         * indicating priority of operands with respect to the '+' operator.
         **/
        s = argv[i-1] + (" " + s + " ") + argv[i-1];
    }

    // Output each element, line by line.
    for(Str::size_type i = 0; i != s.size(); ++i) {
        cout << s[i] << endl;
    }

    // Output divider line
    cout << line << endl;

    // === PART 2: Simple greetings ===

    // Declare a new Str object that will hold the user's input.
    Str name;

    // Prompt user to enter their first name
    cout << "What is your first name?" << endl;

    // Recieve from the input stream the user's input once entered
    cin >> name;

    // Greet the user using their name.
    cout << "\nHello, " << name << "!" << endl;

    // Output the divider line
    cout << line << endl;
}
