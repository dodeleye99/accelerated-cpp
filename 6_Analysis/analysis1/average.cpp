#include <numeric>      // defines std::accumulate
#include <stdexcept>    // defines std::domain_error
#include <vector>       // defines std::vector

#include "average.h"

using std::accumulate;
using std::domain_error;
using std::vector;


// calculates the average of the values in a vector<int>
double average(const vector<int>& v)
{
    vector<double>::size_type size = v.size();

    if (size == 0) {
        throw domain_error("average of an empty vector");
    }
    
    // starting at 0, accumulate (sum) values from the start to the end of the vector
    // then divide by the vector size to get the average
    return accumulate(v.begin(), v.end(), 0) / v.size();

}

// calculates the average of the values in a vector<double>
double average(const vector<double>& v)
{
    vector<double>::size_type size = v.size();

    if (size == 0) {
        throw domain_error("average of an empty vector");
    }
    
    // starting at 0, accumulate (sum) values from the start to the end of the vector
    // then divide by the vector size to get the average
    return accumulate(v.begin(), v.end(), 0.0) / v.size();

}
/**
 * === ALGORITHMS ===
 * accumulate(iter1, iter2, init_value) - starting at init_value, the function sums the values of a containter 
 *  bounded by iterators [iter1, iter2), and returns the new value.
 **/