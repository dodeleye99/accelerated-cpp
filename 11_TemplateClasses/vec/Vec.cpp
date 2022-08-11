#include <algorithm>
using std::max;

#include <cstddef>
using std::ptrdiff_t;

#include <memory>
using std::uninitialized_copy;
using std::uninitialized_fill;

#include "Vec.h"

// === Implementation of the undefined class methods ===

template <class T> 
Vec<T>& Vec<T>::operator=(const Vec& rhs) 
{
    // check for self-assignment, in which case do nothing.
    if(&rhs != this) {

        // free the array in the left hand side
        uncreate();

        // copy elements from the right-hand side to the left-hand side (this object)
        create(rhs.begin(), rhs.end());
    }
    // ensure to return the modified object.
    return *this;
}

template <class T> void Vec<T>::create()
{   
    // initialise the Vec as empty by simply setting all the iterators to 0.
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
    // allocate enough memory for n elements (of type T), setting data to the returned pointer towards the first position
    data = alloc.allocate(n);
    // no extra memory included yet, so have both avail and limit point to the end
    limit = avail = data + n;
    // initialise the elements as copies of val
    uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j)
{   
    /**
     * Allocate enough memory for elements of quantity equal to the distance between the iterators
     * (giving the number of elements in the original sequence). Then set the data member to the returned
     * pointer towards the first allocated position.
     **/
    data = alloc.allocate(j - i);
    /**
     * Initalise the elements as copies of those between the iterators [i, j), 
     * adding them to the dynamic array indicated by data 
     * (returns one past the last element initialised)
     **/
    limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{   
    // we only need to uninitialise if data is not already 0 (indicating an empty Vec)
    if(data) {
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != data)
            alloc.destroy(--it);
        
        // return (free) all the space that was allocated for the Vec elements
        alloc.deallocate(data, size_limit());
        
    }
    // reset pointers to indicate that the Vec is empty again
    data = limit = avail = 0;
}

template <class T> void Vec<T>::grow()
{
    /**
     * While "growing", allocate twice as much space as currently in use
     * (if empty, then allocate only a single space)
     **/
    size_type new_size = max(2 * size_limit(), ptrdiff_t(1));

    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(data, avail, new_data);

    // return (free) the old space
    uncreate();

    // set the iterators to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;

}

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    /**
     * At the end of the sequence of constructed elements, initialise a single element as a copy of val.
     * Then increment avail to point to the next free (pre-allocated), constructable space.  
     **/
    alloc.construct(avail++, val);
}

/**
 * =====================================
 * MEMORY FUCTIONS FROM STANDARD LIBRARY
 * =====================================
 * uninitialized_fill(b, e, x): initialises a yet-to-be constructed sequence (usually a dynamic array)
 *                              bound by iterators [b, e) pointing to the memory locations already 
 *                              allocated for the sequence, assigning each of their values to the 
 *                              value of x.
 * 
 * uninitialized_copy(b, e, d): copies a sequence bound by iterators [b, e) into an already allocated
 *                              memory locations starting from the position indicated by iterator d, 
 *                              initialising a copy of the original sequence, and returns an iterator 
 *                              to the last element of this new sequence.                           
 **/