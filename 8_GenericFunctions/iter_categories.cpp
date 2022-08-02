/**
 * =================================================================
 * A tour of all the different types of iterators that exist in C++
 * =================================================================
 **/

/** 
 * ===================================================
 * Overview - five iterator tiers (lowest to highest):
 * ===================================================
 * (Lowest)
 * #1 Input iterators                 read XOR write
 * #2 Output iterators
 * ---------------------------------------------------
 * #3 Forward iterators                read + write
 * ---------------------------------------------------
 * #4 Bidirectional iterators        reversible access
 * ---------------------------------------------------
 * #5 Random access iterators           any access
 * (Highest)
 * ==================================================
 **/

/**
 * ---------------------------------------
 * CATEGORY #1: Input iterator (read only)
 * ---------------------------------------
 * Summary: sequential read-only access
 * 
 * Supports the following operators:
 * 1) ++ (post and pre)
 * 2) == (and !=)
 * 3) * and -> (deref.)
 **/

// Example: find() function to search for a value x from a sequence bound by two iterators.
template <class In, class X> 
In find1(In begin, In end, const X& x)
{
    // keep searching through the sequence until we have found an iterator pointing to the target
    //  or the end iterator has been reached (indicating unsuccessful search) 
    while (begin != end && *begin != x) 
        ++begin;
        
    // output the iterator we ended the search at.
    return begin;
}
// alternative to above, uses recursion
template <class In, class X> 
In find2(In begin, In end, const X& x)
{
    if (begin == end || *begin == x)
        return begin;
    begin++;
    return find(begin, end, x)
}

/**
 * ----------------------------------------
 * CATEGORY #2: Output iterator (write only)
 * ----------------------------------------
 * Summary: sequential write-only access
 *  
 * Supports the following operators:
 * 1) ++ (post and pre)
 * 2) = (assignment)
 * 3) * (deref. ONLY for assignment)
 * 
 * Can only be written ONCE - no double assignments or double increments (or more) at a time.
 **/

// Example: copy() function to write a sequence of values bound by two iterators to another 
//  destination marked by an iterator.
template <class In, class Out> 
Out copy(In begin, In end, Out dest)
{   

    // Add to the dest iterator the values from the sequence one-by-one, from its beginning to its end.
    // 1) Assign the value pointed to by the destination iterator to the value (access) pointed to by the read iterator.
    // 2) Increment the destination iterator to move to point to the next value or location to be written to.
    // 3) Increment the read iterator to point to the next value to be read.
    while (begin != end)
        *dest++ = *begin++ // {*dest = *begin; ++dest; ++begin;}
}

/**
 * ----------------------------------------------
 * CATEGORY #3: Forward iterator (read and write)
 * ----------------------------------------------
 * Summary: sequential read-write access
 *  
 * Supports the following operators:
 * 1) ++ (post and pre)
 * 2) == (and !=)
 * 3) * and -> (deref.)
 * 4) = (assignment)
 * 
 * Can use assignment more than once unlike output iterators.
 * However, it does not support decrementation (i.e., --it or it--)
 **/

// Example: replace() function to change all instances of a specific value to another given one.
template <class For, class X>
void replace(For beg, For end, const X& x, const X& y)
{
    // Traverse over the values using the iterators, from first to last, replacing all instances of x with y
    while (beg != end) {
        
        if (*beg == x) // input-iterator behavior
            *beg = y;  // output-iterator behavior.
        ++beg;
    }
    
}

/**
 * ----------------------------------------------
 * CATEGORY #4: Bidirectional iterator
 * ----------------------------------------------
 * Summary: Reversible access
 *  
 * Supports the following operators:
 * 1) ++ (post and pre)
 * 2) == (and !=)
 * 3) * and -> (deref.)
 * 4) = (assignment)
 * 5) -- (post and pre)
 * 
 * We see that it supports all operations of forward iterator, as well as decrementation (--).
 **/

// Example: reverse() function to reverse the order of the elements of a sequence bound by iterators.
// Reversible access
template <class Bi> 
void reverse(Bi begin, Bi end)
{   
    // continue until both sides point to the same location.
    while (begin != end) {
        // fall-back the end iterator
        --end;
        // swap the values at the two current ends of the sequence pointed to
        if(begin != end)
            // after the swap, advance the begin iterator
            swap(*begin++, *end); // { swap(*begin, *end); ++begin; }
    }
    /**
     * Example of the process:
     *  0 1 2 3 4 5
     * [A B C D E F] initial:   begin = 0, end = 6
     * [F B C D E A] 1st pass:  begin = 1, end = 5
     * [F E C D B A] 2nd pass:  begin = 2, end = 4
     * [F E D C B A] 3rd pass:  begin = 3, end = 3
     * (begin == end, so end loop)
     **/
}

/**
 * ----------------------------------------------
 * CATEGORY #5: Random access iterator
 * ----------------------------------------------
 * Summary: Random (any-point) access - most powerful iterator
 *  
 * Supports all the other usual iterator properties from bidirectional, namely:
 * 1) ++ (post and pre)
 * 2) == (and !=)
 * 3) * and -> (deref.)
 * 4) = (assignment)
 * 5) -- (post and pre)
 * 
 * But it also supports the following:
 * (Let p and q be random access iterators, and n an integer)
 * 6) p + n, p - n, n + p           (addition of an iterator and an integer, yields another iterator)
 * 7) p - q                         (subtraction of one iterator from another, yields an integer representing distance between them)
 * 8) p[n]                          (equivalent to *(p+n) )
 * 9) p < q, p > q, p <= q, p >=q   (comparing two iterators using inequalities.)
 **/

// Example: binary_search() function to determine whether a given value exists in a SORTED sequence bound by random-access iterators.
// (Method of search is not sequential, but divide and conquer)
template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x)
{   
    // if the begin iterator is the same or goes past the end iterator, then the value is not found.
    while (begin < end) {
        // find the midpoint of the range
        Ran mid = begin + (end - begin) / 2;
        // see which part of the range contains x; keep looking only in that part
        if (x < *mid)
            // discard the upper half by setting the end iterator to point to the midpoint.
            end = mid;
        else if (*mid < x)
            // discard the lower half by setting the begin iterator to point to one-past the midpoint.
            begin = mid + 1;
        // if we got here, then *mid == x so we're done
        else return true;
    }
    return false;
}
