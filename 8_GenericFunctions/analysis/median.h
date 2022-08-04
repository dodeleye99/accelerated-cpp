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
 * Calculates the median of the (assumed numerical) values in a sequence defined by 
 * the range of iterators [b, e)
 * 
 * Iterator required: random access iterator 
 **/
template<class Ran> 
double median(Ran b, Ran e)
{
    /**
     * (The ptrdiff_t type is used to define differences between pointers.)
     * 
     * Get the size of the sequence by calculating the distance between the iterators.
     * For random access iterators, it can be found using the subtration operator.
     **/
    const std::ptrdiff_t size = e - b;

    // throw an error if the size is zero (empty sequence)
    if (size == 0) {
        throw std::domain_error("median of an empty container");
    }

    // use the size to calculate the midpoint of the sequence.
    std::ptrdiff_t mid  = size / 2;

    // use a copy of the sequence to prevent the original from being modified.
    std::vector<double> v(b, e);
    
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