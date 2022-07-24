#include <iomanip>      // defines std::setpecision and other manipulators
#include <ios>          // defines std::streamsize    
#include <iostream>     // defines std::cin, std::cout and std::endl
#include <string>       // defines std::string

using std::cin;         using std::setprecision;
using std::cout;        using std::string;
using std::endl;        using std::streamsize;


// This procedure is used to output the greeting.
void output_greeting(string greeting)
{
    // the number of blanks surrounding the greeting
    const int pad = 2;

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
    // ask for and read the student's name
    cout << "Please enter your first name: ";
    string name;
    cin >> name;

    const string greeting = "Hello, " + name + "!";
    output_greeting(greeting);

    // ask for and read the midterm and final grades
    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;

    // ask for homework grades
    cout << "Enter all your homework grades, "
            "followed by end-of-file: "; // On macOS: new line, then ctrl-d

    // The number and sum of grades read so far
    int count = 0;
    double sum = 0;

    // a variable into which to read
    double x;

    // invariant: (special care needed since the condition of the loop has side effects, i.e. reading into x)
    //      we have read 'count' grades so far, and
    //      'sum' is the sum of the first 'count' grades
    while (cin >> x) {
        ++count;
        sum += x;
    }

    // write the result
    streamsize prec = cout.precision();
    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
         << setprecision(prec) << endl;

    return 0;
}

/**
 * - 
 * - 'double' is a type used for double-precision floating-point numbers.
 * - setprecision(int sf): a manipulator that sets the number of significant figures of decimal numbers outputted to 'sf'.
 * - streamsize is a type that the io library uses to represent sizes.
 **/
