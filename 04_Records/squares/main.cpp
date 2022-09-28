// calculate the squares of 0 to a given number


#include <cmath>    // defines sqrt, pow
#include <iostream> // defines cin, cout, endl
#include <iomanip>  // defines setw
#include <string>   // defines string
#include <ios>      // defines streamsize

using std::cin;
using std::cout;
using std::endl;
using std::pow;
using std::setw;
using std::sqrt;
using std::string;
using std::streamsize;


// calculates the number of digits of a given integer
streamsize get_digits(int n)
{
    /**
     * An illustration of how get_digits works:
     *     (1)            (2)          (3)        (4)
     * 2567 -> 256.7 ~ 256 -> 25.6 ~ 25 -> 2.5 ~ 2 -> 0.2~0
     * Thus get_digits(2567) = 4.
    **/

    // the special case, zero, has one digit
    if(n == 0) {
        return 1;
    }

    streamsize count = 0;

    while(n != 0) {
        n /= 10;
        ++count;
    }
    return count;
}


int main()
{   
    // to hold the cap for the sequence of numbers to calculate squares from
    int limit;

    // introduce the program to the user.
    cout << "This program lists the square numbers of consecutive integers "
            "starting from 0." << endl;

    // prompt the user to enter the final number to calculate squares from.
    cout << "Which number would you like the consecutive integers to end at?"
        << endl;

    // feed the user's input into the variable.
    cin >> limit;

    // complian and exit if the input stream had problems reading the input.
    if(!cin) {
        // interpret this as the user failing to enter an integer.
        cout << "Invalid input. You must enter a whole number." << endl; 
        return -1;
    }
    
    // complain and exit if the user entered a negative number.
    if(limit < 0) {
        cout << "Invalid input. The integer must be positive." << endl; 
        return -1;
    }

    /**
     * Use get_digits() to find out how many digits are in 999 (and its square).
     * This will help us know the padding we need to neatly output the table of
     * values.
    */
    streamsize max_digits = get_digits(limit);

    // prepare to list the squares.
    cout << "\nThe squares of integers from 0 to " << limit << ":" << endl;

    for(int i = 0; i != limit + 1; ++i) {
        
        // end the loop early if INT_MAX will be surpassed 
        // (to prevent overflows).
        if(i > sqrt(INT_MAX)) {
            cout << "Stopping early, squares are getting too big." 
                << endl;
            // (use the break statement to exit the loop entirely.)
            break;
        }
        /**
         * Technically, larger numbers can be calculated, by using, 
         * instead of the int type, a type that can store even larger 
         * numbers, such as long.
         **/

        // calculate the square of the current number traversed over.
        int square = pow(i, 2);

        // find an apporiate padding.
        streamsize pad = max_digits - get_digits(i) + 1 + get_digits(square);

        // use setw() to write blank space of a given length.
        // alternatively, initialise a string of blank space.
        cout << i << setw(pad) << square << endl;
    }
    return 0;
}

