// Guard the header file from multiple inclusions, to prevent an error.
#ifndef GUARD_median_h
#define GUARD_median_h

// median.h
#include <algorithm>    // defines std::sort and std::max
#include <cstddef>      // defines std::ptrdiff_t
#include <stdexcept>    // defines std::domain_error
#include <vector>       // defines std::domain_error
#include <iostream>


/**
 * Calculates the median of the (assumed numerical type T) values in a sequence defined by 
 * the range of iterators [b, e)
 * 
 * Iterator required: random access iterator 
 **/
template<class T, class Ran> 
double median(Ran b, Ran e)
{

    // throw an error if the iterators are at the same position (empty sequence)
    if (b == e) {
        throw std::domain_error("median of an empty container");
    }

    // use a copy of the sequence to prevent the original from being modified.
    std::vector<T> v(b, e);
    
    // get the size of the sequence by calculating the distance between the iterators.
    std::size_t size = v.size();

    // use the size to calculate the midpoint of the sequence.
    std::size_t mid  = size / 2;
    
    // ensure the sequence is sorted to ensure a correct result.
    std::sort(v.begin(), v.end());

    /**
     * Calculate the median: 
     * - If the size is even, then the median is equal to the sum of the value in the mid position and the previous one.
     * - Otherwise (if size is odd), the median is equal to the element in the mid position.
     **/
    return size % 2 == 0 ?  (v[mid] + v[mid-1]) / 2.0 : v[mid];
}

#endif
