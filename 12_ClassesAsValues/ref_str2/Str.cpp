#include <algorithm>
using std::copy;
using std::max;

#include <cctype>
using std::isspace;

#include <cstring>
using std::strcmp;

#include <iostream> 
using std::istream;
using std::ostream;

#include <iterator>
using std::ostream_iterator;

#include <memory>
using std::uninitialized_copy;
using std::uninitialized_fill;

#include "Str.h"

// =============== Implementation of the undefined class methods ===============

// -------- Memory allocation/deallocation functions --------
void Str::create()
{   
    // initialise the Str as empty by simply setting all the iterators to 0.
    dta = avail = limit = 0;

    // allocate memory for the character-array copy used for conversions.
    allocate_c();
}

void Str::create(size_type n, const char& c)
{
    // allocate enough memory for n elements (of type char), setting data to the returned pointer towards the first position
    dta = alloc.allocate(n);
    // no extra memory included yet, so have both avail and limit point to the end
    limit = avail = dta + n;
    // initialise the elements as copies of c
    uninitialized_fill(dta, limit, c);

    // allocate memory for the character-array copy used for conversions.
    allocate_c();
}

template <class In> void Str::create(In i, In j)
{
    /**
     * Allocate enough memory for elements of quantity equal to the distance between the iterators
     * (giving the number of elements in the original sequence). Then set the data member to the returned
     * pointer towards the first allocated position.
     **/
    dta = alloc.allocate(j - i);
    /**
     * Initalise the elements as copies of those between the iterators [i, j), 
     * adding them to the dynamic array indicated by data 
     * (returns one past the last element initialised)
     **/
    limit = avail = uninitialized_copy(i, j, dta);

    // allocate memory for the character-array copy used for conversions.
    allocate_c();
}

void Str::uncreate()
{
    // we only need to uninitialise if dta is not already 0 (indicating an empty Str)
    if(dta) {
        // destroy (in reverse order) the elements that were constructed
        iterator it = avail;
        while (it != dta)
            alloc.destroy(--it);
        
        // return (free) all the space that was allocated for the Vec elements
        alloc.deallocate(dta, size_limit());
        
    }
    // reset pointers to indicate that the Vec is empty again
    dta = limit = avail = 0;

    // destroy and dellocate the memory of the character-array copy.
    allocate_c();
}

// -------- Support ("helper") functions for the insert member function -------

void Str::grow()
{
    // if no minimun space is specified, we pass 0, indicating no required threshold to meet.
    grow(0);   
}

void Str::grow(size_type min_space)
{
    // create a variable that will mark the new maximum size.
    size_type new_size = size_limit();
    do
    {
        /**
         * While "growing", allocate twice as much space as currently in use
         * (if empty, then allocate only a single space)
         * 
         * If the new space is below the minimum space need, we keep 
         * growing until it it large enough.
         **/ 
        new_size = std::max(2 * new_size, size_type(1));
    } 
    while (new_size < min_space);

    // allocate new space and copy existing elements to the new space
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = uninitialized_copy(dta, avail, new_data);

    // return (free) the old space
    uncreate();

    // set the iterators to point to the newly allocated space
    dta = new_data;
    avail = new_avail;
    limit = dta + new_size;
}

Str::iterator Str::unchecked_insert(iterator position, const char& c)
{
    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * by one place. This leaves room to insert the new value into the array at the given position.
     **/

    // create a variable holding the current end of the Str
    iterator it = avail;

    // shift values up the array, until we reach the given postiion.
    while (it != position) {
        // initialise the value at the current position using the value at the position before it
        alloc.construct(it, *(it-1));
        // destroy the value at the postiion just copied from, and more to that position.
        alloc.destroy(--it);
    }
    // finally construct an element at the position from the given value.
    alloc.construct(it, c);

    // remember to increment the pointer to the end of the Str, since one element has just been added.
    ++avail;
    
    // return the iterator to the inserted element.
    return it;
}

template <class In> void Str::unchecked_insert(iterator position, In first, In last, difference_type dist)
{
    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * enough so that there is room to insert the new values into the array from the given position.
     **/
    
    /**
     * Create a variable holding where the new end of the Str will be when after the values are inserted.
     * It will be used for constructing elements at new postions.
     **/
    iterator it1 = avail + dist;
    /**
     * Create another variable holding the current end of the Str - will be used for destructions..
     * It will be used for destroying elements at original postions.
     **/
    iterator it2 = avail;

    // shift values up the array, until we reach the given postiion.
    while (it2 != position) {
        /**
         * Decrement the iterators, then initialise the value at the "construction" 
         * position using the value at the "destruction" position
         **/
        alloc.construct(--it1, *(--it2));
        // destroy the value at the "destruction" postiion just copied from.
        alloc.destroy(it2);
    }
    // finally, starting from the given position, construct elements from the values in the given range [first, last).
    std::uninitialized_copy(first, last, position);

    // remember to increase the pointer to the end of the Str, since multiple elements have just been added.
    avail += dist;
}

void Str::unchecked_insert(iterator position, size_type n, const char& c)
{
    // (VERY SIMILAR to the range version. Only difference is that here the same value is inserted at each position)

    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * so that there is enough room to insert the new values into the array from the given position.
     **/
    
    /**
     * Create a variable holding where the new end of the Str will be when after the values are inserted.
     * It will be used for constructing elements at new postions.
     **/
    iterator it1 = avail + n;

    /**
     * Create another variable holding the current end of the Str - will be used for destructions.
     * It will be used for destroying elements at original postions.
     **/
    iterator it2 = avail;

    // shift values up the array, until we reach the given postiion.
    while (it2 != position) {
        /**
         * Decrement the iterators, then initialise the value at the "construction" 
         * position using the value at the "destruction" position
         **/
        alloc.construct(--it1, *(--it2));
        // destroy the value at the "destruction" postiion just copied from.
        alloc.destroy(it2);
    }

    // finally, starting from the given position, construct n elements from the given character.
    std::uninitialized_fill(position, position + n, c);

    // remember to increase the pointer to the end of the Str, since n elements have just been added.
    avail += n;
}

// -------- Support ("helper") functions for the erase member function -------

Str::iterator Str::erase_chars(iterator position)
{
    // create a variable holding the position of the element to erase.
    iterator it = position;

    // destory the element, then advance the iterator to point to the element after it.
    alloc.destroy(it++);

    // "shift" to the "left" the constructed elements in the underlying array.
    while (it != avail) {
        // initialise an element at the previous positon from the value of the current pointed element.
        alloc.construct(it - 1, *it);
        // destroy the element at the current position (to be reconstructed), moving to the next.
        alloc.destroy(it++);
    }

    // set avail to where it previously pointed to, since this now marks the first free (unconstructed) space.
    avail = it - 1;
    
    // return the position argument, now pointing to the element coming after the one just erased.
    return position;
}

Str::iterator Str::erase_chars(iterator b, iterator e)
{
    // destroy the elements in the given range
    for(iterator it=b; it != e; ++it) {
        alloc.destroy(it);
    }

    /**
     * Now we must to "shift" every element in the range [e, avail) down to position b in the array.
     * We use copies of the iterators defining range of the destroyed elements.
     **/
    iterator it1 = b;  // for constructing elements
    iterator it2 = e;  // for destroying elements
    
    // shift values up the array, until we reach the end of the Str.
    while (it2 != avail)
    {   
        /**
         * Initialise the value at the "construction" position using the value at the "destruction" position.
         * Then move the "construction" position up by one.
         **/
        alloc.construct(it1++, *it2);
        /**
         * Destroy the value at the "destruction" postiion just copied from.
         * Then move the "destruction" position up by one.
         **/
        
        alloc.destroy(it2++);
    }

    // The new end position will be the left-most position with a destoyed element - where it1 stopped.
    avail = it1;

    /**
     * Output the position of the first of the erased elements. This position marks the new position of 
     * the element coming after the range of the erased elements.
     **/
    return b;   
}

// -------- Functions used to construct and destroy the stored character array --------

void Str::allocate_c()
{   
    /**
     * Allocate enough space for all the characters making up the Str object, with two extra spaces
     * for an 'init flag' and a terminating null-character (for c_str()).
     * 
     * (Note the use of the new keyword instead of using the allocator object. Since the char type is
     * primitive, they are not default constructed, thus this method of dynamic allocation/construction 
     * no less efficient than the allocator's method.)
     **/
    c = new char[size() + 2];

    // Set the 'flag' element to the null character, indicating that the array is yet to be set up.
    c[0] = '\0';
}

void Str::deallocate_c() {  delete[] c; }

void Str::reallocate_c(bool do_check) {
        
    // unless the check should be ignored, do nothing if the 'init flag' indicates not yet setup ('\0').
    if(!do_check || *c) {
        // deallocate the space taken by the array
        deallocate_c();
        // allocate space for a new array
        allocate_c();
    }
}

void Str::reallocate_c() {
    // when no argument is specified, by default the array checked for whether it is already setup.
    reallocate_c(true);
}

// ====================================================================================================

// ------------------- Implementation of the non-member functions and operators -------------------

ostream& operator<<(ostream& os, const Str& s) 
{   
    /**
     * Copy the characters of the Str object to the output stream, using an ostrem_iterator object
     * to represent an iterator to the current position of the stream to write the characters to.
     **/
    copy(s.begin(), s.end(), ostream_iterator<char>(os));

    /**
     * Remember to return the output stream, to allow for repeated writes
     * (i.e. os << s1 << s2 ... << sn)
     **/
    return os;
}

istream& operator>>(istream& is, Str& s) 
{   
    // obliterate existing value(s), to ensure it is entirely replaced with the text read by the stream
    s.clear();

    // declare a new char used to store characters read by the strem
    char c;

    /**
     * Read and discard leading whitespace. That is, continuously pass characters that are whitespaces,
     * until one that is not a whitespace is found (or if end-of-file is reached).
     **/
    while(is.get(c) && isspace(c))
        ; // nothing to do, except testing condition
    
    /**
     * If there is still something to read (not yet an end-of-file), do so until the next whitespace character,
     * adding each character being read to the end of the Str.
     **/
    if (is) {
        do s.push_back(c);
        while (is.get(c) && !isspace(c));

        // if we read whitespace (and not because of end-of-file that we stopped reading), then put it back on the stream
        if(is)
            is.unget();
    }

    /**
     * Remember to return the output stream, to allow for repeated reads
     * (i.e. is >> s1 >> s2 ... >> sn)
     * and to immediately check its state - for example,
     * while(is >> s)
     *  // add s to a Vec<Str>
     **/
    return is;
}

Str operator+(const Str& s, const Str& t)
{
    // construct a copy of one of the first operand
    Str r = s;
    // concatenate the other operand to the end of this copy
    r += t;
    /**
     * Return the final result (a copy, since the original copy defined in this scope will be destroyed).
     * This also enables us to create a chain of concatenations
     * (i.e. s1 + s2 + ... + sn).
     **/
    return r;
}


Str operator+(const char* s, const Str& t) { 

    // use the conversion constructor to create a Str out of the first operand (a c-string).
    Str r = s;
    // concatenate the second (Str) operand to the end of this converted Str.
    r += t; 
    // return the final result
    return r; 
}

/**
 * ==============
 * IMPORTANT NOTE
 * ==============
 * Concatenation is NOT commutative ((s + t) != (t + s)). 
 * So we cannot simply swap the parameters and call the above.
 * 
 * Also it is better that we do not convert the character array to a Str and call on the 
 * operator+ overload that takes two strings. It is more efficient to write it the usual 
 * way as those above, relying only on Str::operator+=.
 **/
Str operator+(const Str& s, const char* t) { 
    // construct a copy of the first operand (Str object)
    Str r = s;
    // concatenate the second (c-string) operand to the end of this copy.
    r += t;
    // return the final result
    return r;
}

Str operator+(char c, const Str& s) { 
    // construct a string containing only a single character, given by the first operand (char object)
    Str r(1, c);
    // concatenate the second (Str) operand to the end of this Str.
    r += s;
    // return the final result
    return r;
}

Str operator+(const Str& s, char c) {
    // construct a copy of the first operand (Str object)
    Str r = s; 
    // concatenate the second (a single character) operand to the end of this copy.
    r += c;
    // return the final result
    return r; 
}

bool operator<(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

bool operator>(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

bool operator<=(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) <= 0;
}

bool operator>=(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) >= 0;
}

bool operator==(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

bool operator!=(const Str& lhs, const Str& rhs) {
    return strcmp(lhs.c_str(), rhs.c_str()) != 0;
}

istream& getline(istream& is, Str& s, char delim)
{
    // obliterate existing value(s), to ensure it is entirely replaced with the text read by the stream
    s.clear();

    // declare a new char used to store characters read by the stream
    char c;

    /**
     * Until an end-of-file (or istream error) is reached, or a delimiter is found, read and add each 
     * non-delimiter character to the end of the Str. The delimiter found is extracted from the stream 
     * and discarded.
     **/
    while(is.get(c) && c != delim) {
        s.push_back(c);
    }
    
    // output the istream, allowing the user to tell the state of the stream after the operation.
    return is;
}

istream& getline(istream& is, Str& s){ return getline(is, s, '\n'); }


/**
 * ============================
 * New istream member functions
 * ============================
 * 
 * istream::get(c)  - reads whatever character is next to be read in the input stream, including whitespace.
 *                    the value read is then assigned to the given char reference c. It returns the istream 
 *                    itself, enabling one to check immediately whether it has reached end-of-file or 
 *                    otherwise.
 *
 * istream::unget() - decrements the current location of the input stream by undoing the most recent get(),
 *                    effectively backspacing the stream by one character and so returning exactly to the 
 *                    state it was before the most recent character was read.
 **/

/**
 * ================================
 * Function used to compare strings
 * ================================
 * strcmp(p1, p2) - lexographically compares two c-strings (null-terminated character arrays), represented by 
 *                  pointers to their first element. Returns an integer whose sign indicates their order.
 *                      
 *                  if strcmp < 0: then the first c-string appears before the second.
 *                  if strcmp = 0: then the both c-strings are the equal.
 *                  if strcmp > 0: then the first c-string apperas after the second. 
 **/