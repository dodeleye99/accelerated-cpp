#include <algorithm>    // defines std::sort and std::max
#include <stdexcept>    // defines std::domain_error
#include <vector>       // defines std::vector

using std::domain_error;
using std::sort;
using std::vector;


// compute the median of a vector<int>
// note that calling this function copies the entire argument vector (i.e. call by value), thus the sort() function causes no side effects
double median(vector<int> vec)
{
    // use the name 'vec_sz' as a synonym for vector<double>::size_type, so that it is easier to read and write.
    typedef vector<int>::size_type vec_sz;

    // get the number of elements in the vector
    vec_sz size = vec.size();

    // if the size is zero, then no median exists.
    if (size == 0) {
        // throw an exception of the appropriate type
        throw domain_error("median of an empty vector");
    }

    // sort the elements of the vector, from the first to the last, in monotonic increasing order. (i.e. non-decreasing)
    sort(vec.begin(), vec.end());

    // Calculate the midpoint (rounded down to nearest integer) of the vector
    vec_sz mid = size/2;

    // calculate the median: 
    // - if the size is even, then the median is equal to the sum of the element in the mid position and the previous one.
    // - otherwise (if size is odd), the median is equal to the element in the mid position.
    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2.0 : vec[mid];

    // alternatively, we could have written:
    // if (size % 2 == 0)
    //     return (vec[mid] + vec[mid-1])/2;
    // else
    //     return  vec[mid];
}
