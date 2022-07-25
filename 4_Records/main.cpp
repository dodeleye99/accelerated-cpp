// calculate the squares of 0 to 999
#include <iostream> // defines cout, endl
#include <iomanip>  // defines setw
#include <string>   // defines string
#include <ios>      // defines streamsize

using std::cout;
using std::endl;
using std::setw;
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

    // The special case, zero, has one digit
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
    /**
     * Use get_digits() to find out how many digits are in 999 (and its square).
     * This will help us know the padding we need to neatly output the table of values.
    */
    int count = 999;
    streamsize max_digits = get_digits(count);

    cout << "The squares of integers from 0 to " << count << ":" << endl;
    for(int i = 0; i != count + 1; ++i) {

        int square = i * i;
        // find an apporiate padding.
        streamsize pad = max_digits - get_digits(i) + 1 + get_digits(square);
        // use setw() to write blank space of a given length.
        // alternatively, initialise a string of blank space.
        cout << i << setw(pad) << square << endl;
    }
    return 0;
}

