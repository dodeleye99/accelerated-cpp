// this program calculates quartiles of a sequence of numbers.
#include <algorithm> 
#include <iomanip> 
#include <ios>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::vector;


// This function does interpolation between two adjacent values of a vector.
// The parameter 'left_index' indicates the index of the value with the lesser index.
double interpolate(vector<int> integers, int left_index, double factor) {
    double left = integers[left_index];
    double right = integers[left_index + 1];
    return left + (right - left) * factor;
}

int main()
{
    // Prompt user to input a set of integers.
    cout << "Input a set of integers to find the quartiles, "
            "followed by end-of-file: "; // On macOS: new line, then ctrl-d;

    // define a variable into which the integers are read into one by one
    int x;
    // define vector that will hold all the integers
    vector<int> integers;

    // invariant: 'integers' holds all the integers read so far.
    while(cin >> x) {
        // append x at the end of the 'integers' vector
        integers.push_back(x);
    }

    // use the name 'vec_sz' as a synonym for vector<int>::size_type, so that it is easier to read and write.
    typedef vector<int>::size_type vec_sz;

    // get the number of elements in the vector
    vec_sz size = integers.size();

    // If the size is zero, then no integers were entered.
    if (size == 0) {
        cout << endl << "You must enter a sequence of integers. "
                        "Please try again." << endl;
        // End the program, returning non-zero value to indicate failure.
        return 1;       
    }

    sort(integers.begin(), integers.end());
    
    double lower_quartile, median, upper_quartile;

    if(size == 1) {
        lower_quartile = integers[0];
        median = integers[0];
        upper_quartile = integers[0];
    } 
    else {
        vec_sz last_index = size - 1;

        // Get the index value of each quartile, rounded down to nearest integer.
        vec_sz low = last_index / 4;
        vec_sz mid = last_index / 2;
        vec_sz up  = (3 * last_index) / 4;

        // Calculate the interpolation factor, determining how 'far' we should approach the value at the next index.
        double l_factor = (last_index % 4) / 4.0;
        double m_factor = (last_index % 2) / 2.0;
        double u_factor = ((3 * last_index) % 4 ) / 4.0;
        
        // Do interpolation to determine the quartile values.
        lower_quartile = interpolate(integers, low, l_factor);
        median         = interpolate(integers, mid, m_factor);
        upper_quartile = interpolate(integers, up, u_factor);
    }

    streamsize prec = cout.precision();
    cout << endl << setprecision(4) 
         << "Minimum: " << integers[0] << endl 
         << "Lower Quartile: " << lower_quartile << endl
         << "Median: " << median << endl
         << "Upper Quartile: " << upper_quartile << endl
         << "Maximum: " << integers[size - 1]
         << setprecision(prec) << endl;
    
    return 0;
}

/**
 * 
 * V = |A|B|C|   size = 3, low = 0, up = 2, median = V[1] = B
 * 
 * 
 * |0|1|2|3|4|5|6|7|8|9|


 * V = |A|B|C|D| size = 4, lower = 1, upper = 3, 
 * lower_quartile = (V[lower] + V[lower - 1])/2 =  (A + B)/2
 * upper_quartile = (V[upper] + V[upper - 1])/2 =  (C + D)/2
 **/
