// Guard the header file from multiple inclusions, to prevent an error.
#ifndef GUARD_average_h
#define GUARD_average_h

// average.h
#include <numeric>      // defines std::accumulate
#include <stdexcept>    // defines std::domain_error

#include "zero.h"       // defines the zero<T> function template


/**
 * Calculates the average of the values in a sequence bound by iterators [b, e)
 * 
 * Iterator required: input iterator 
 **/
template<class In> 
double average(In b, In e)
{
    // throw an error if iterators are the same (empty sequence)
    if (b == e) {
        throw std::domain_error("average of an empty container");
    }

    /**
     * Starting at 0 (matching the type of the sequence values),
     * accumulate (sum) the values from the start and the end of the sequence.
     * 
     * Then divide by the distance/difference between the iterators to get the average
     **/
    return std::accumulate(b, e, zero<double>()) / std::distance(b, e);
}

#endif