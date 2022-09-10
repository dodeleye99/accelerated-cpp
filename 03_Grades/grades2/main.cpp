#include <algorithm>    // defines std::sort
#include <iomanip>      // defines std::setpecision and other manipulators
#include <ios>          // defines std::streamsize    
#include <iostream>     // defines std::cin, std::cout and std::endl
#include <string>       // defines std::string
#include <vector>       // defines std::vector

using std::cin;             using std::sort;
using std::cout;            using std::streamsize;
using std::endl;            using std::string;
using std::setprecision;    using std::vector;


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
    
    // define a variable into which the homework grades are read into one by one
    double x;
    // define vector that will hold all the homework grades
    vector<double> homework;

    // invariant: 'homework' contains all the homework grades read so far
    while(cin >> x)
        // append x at the end of the 'homework' vector
        homework.push_back(x);

    // use the name 'vec_sz' as a synonym for vector<double>::size_type, so that it is easier to read and write.
    typedef vector<double>::size_type vec_sz;

    // get the number of elements in the vector
    vec_sz size = homework.size();

    // If the size is zero, then no grades were entered.
    if (size == 0) {
        cout << endl << "You must enter your grades. "
                        "Please try again." << endl;
        // End the program, returning non-zero value to indicate failure.
        return 1;

    }

    // -- COMPUTING THE MEDIAN HOMEWORK GRADE --

    // sort the elements of the vector, from the first to the last, in monotonic increasing order. (i.e. non-decreasing)
    sort(homework.begin(), homework.end());

    // Calculate the midpoint (rounded down to nearest integer) of the vector
    vec_sz mid = size/2;

    // Calculate the median: 
    // - if the size is even, then the median is equal to the sum of the element in the mid position and the previous one.
    // - otherwise (if size is odd), the median is equal to the element in the mid position.
    double median; 
    median = size % 2 == 0 ? (homework[mid] + homework[mid-1])/2 : homework[mid];

    // Alternatively, we could have written:
    // if (size % 2 == 0)
    //     median = (homework[mid] + homework[mid-1])/2;
    // else
    //     median =  homework[mid];

    // --                                   --

    // compute and write the final grade
    streamsize prec = cout.precision();
    cout << "Your final grade is " << setprecision(3)
         << 0.2 * midterm + 0.4 * final + 0.4 * median
         << setprecision(prec) << endl;

    return 0;

}

/**
 * - 
 * - 'vector' is a container that holds a collection of values.
 * - typedef is used to create a new identifier for a given type. (typedef 'type' 'name';)
 * 
 * - (Conditional operator) 'x ? y : z' means "if x is true, then return y. Otherwise return z."
 * 
 * - if (x)
 *      y;
 *   else
 *      z;
 **/

/** Examples of the median of a set of data
 *      0 1 2 3
 * V = |A|B|C|   size = 3, mid = 1, median = V[1] = B
 * V = |A|B|C|D| size = 4, mid = 2, median = (V[2] + V[1])/2 = (B + C)/2
 **/ 
