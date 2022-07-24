#include <iostream>
#include <string>

// say what standard-library names we use
using std::cin;             using std::endl;
using std::cout;            using std::string;


// This procedure is used to output the greeting.
void output_greeting(string greeting)
{
    // the number of blanks surrounding the greeting
    const int pad = 3;

    // total number of rows and columns write
    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;

    // write a blank line to separate the output from the input
    cout << endl;

    // write 'rows' rows of output
    // invariant: we have written 'r' rows so far
    for(int r = 0; r != rows; r++) {

        string::size_type c = 0;

        // invariant: we have written c characters so far in the current row
        while (c != cols) {

            // is it time to write the greeting?
            if(r == pad + 1 && c == pad + 1) {
                cout << greeting;
                c += greeting.size();
            } else {
                // are we on the border?
                if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
                    cout << "*";
                else
                    cout << " ";
                ++c;
            }
        } 

        cout << endl;
    }
}


int main()
{
    // ask for the person's name
    std::cout << "Please enter your first name: ";

    // read the name
    string name;
    cin >> name;

    // build the message that we intend to write
    const string greeting = "Hello, " + name + "!";
    
    // output the greeting.
    output_greeting(greeting);

    return 0;
}

// The general structure of a function:
// <return-type> <function-name>(<arg-type1> <arg-name2>, <arg-type2> <arg-name2>, ...)
// If <return-type> is void, then the function will not return any value at all.