#ifndef GUARD_Vec_h
#define GUARD_Vec_h

#include <algorithm>    // std::max;
#include <cstddef>      // std::ptrdiff_t and std::size_t
#include <iterator>     // std::distance, std::iterator_traits<It>
#include <memory>       // std::allocate<T>, std::uninitialized_copy, std::uninitialized_fill


/**
 * A custom "category" of classes used to represent a vector of elements of a particular type
 * ===============
 * CLASS INVARIANT
 * ===============
 * 1) data points to our initial element, if we have any, and is zero otherwise
 * 2) data <= avail <= limit
 * 3) Elements have been constructed in the range [data, avail)
 * 4) Elements have not been constructed in the range [avail, limit).
 **/
template <class T> class Vec {

// ---- Public (free access) members, representing the interface ---- 
public:
    
    // ---------- Type definitions ----------
    typedef T* iterator;                        // type used for iterating over elements of the contanier.
    typedef const T* const_iterator;            // constant iterator type used for read-only access 
    typedef std::size_t size_type;              // type used to represent size of the container
    typedef T value_type;                       // type used to represent the type of the elements stored
    typedef std::ptrdiff_t difference_type;     // type used to represent distance between iterators (by subtraction)
    typedef T& reference;                       // type used for defining references to an object of value_type
    typedef const T& const_reference;           // constant reference type used for read-only access

    // --------------- Constructors ---------------
    
    // default constructor
    Vec() { create(); } 
    // copy constructor                                
    Vec(const Vec& v) { create(v.begin(), v.end()); }

    /**
     * 'fill' constructor, creating a Vec consisting of n copies of val.
     * 
     * The "explicit" keyword here means that one must write (initialisation) 
     * Vec<double> v(n) rather than 
     * Vec<double> v = n (which is implicitly the above)
     * (where n is an int)
     * 
     * From the expression Vec<double> v = n, the compiler will attempt to call a constructor of Vec that
     * can take a single integer value of type 'int', to use for constructing v.
     * This constructor fits these requirements, since 'int' can automatically be converted to 'size_type'.
     * 
     * But the "explicit" keyword prevents the compiler from writting such an expression with '=' operator 
     * to do this implicit constructor call. Instead it must be specified explicitly.
     **/
    explicit Vec(size_type n, const T& val = T()) { create(n, val); }

    // range constructor: create a Vec from the range denoted by iterators b and e
    template <class In> Vec(In b, In e) {
        create(b, e);
    }

    // --------------- Destructor ---------------
    ~Vec() { uncreate(); }  

    // --------------- Operators ----------------

    // the assignment operator
    Vec& operator=(const Vec&);

    // indexing operator, returning a reference to the element at a given position.
    T& operator[](size_type i) { return data[i]; }
    // (for read-only)
    const T& operator[](size_type i) const { return data[i]; }

    // --------------- Member functions ---------------

    // ---- Iterators ----
    
    // outputs an iterator to the first element of the Vec
    iterator begin() { return data; }
    // (read-only iterator)
    const_iterator begin() const { return data; }

    // outputs an iterator to the end of the Vec (one-past the last element)
    iterator end() { return avail;}
    // (read-only iterator)
    const_iterator end() const {return avail; }

    // ---- Capacity functions ----

    // outputs the number of elements in the Vec
    size_type size() const { return avail - data; }

    // a predicate for whether the Vec is empty (no elements).
    bool empty() const { return data == avail; }

    /**
     * Modifies the Vec such that the number of elements stored in it is changed
     * to match a given size.
     * 
     * If the given size is greater than the current size, the Vec is filled up
     * with new elements, initialised by a given value, to reach the
     * required size. 
     * 
     * If the given size is less than the current size, then elements 
     * from the end of the Vec are erased to make the Vec have the required
     * size.
     * 
     * If the given size matches the current size, nothing happens.
     **/
    void resize(size_type n, T val = T()) {

        // get the current size of the Vec.
        size_type sz = size();

        // if above the given size, erase enough elements from the end.
        if(sz > n) {
            erase(avail - (sz - n), avail);
        }

        // if below the given size, insert enough copies of the given value to the end.
        else if(sz < n){
            insert(avail, n - sz, val);
        }
    }

    // ---- Modifiers ----

    // adds an element to the end of the Vec.
    void push_back(const T& t) {
        // this is equivalent to inserting an element at the end of the Vec.
        insert(avail, t);
    }

    /**
     * Inserts a given value into the Vec BEFORE the element at the given position 
     * (if the end, then this is simply a push_back), returning an iterator to this 
     * inserted element.
     **/
    iterator insert(iterator position, const T& v){ 
        // get space if needed
        if (avail == limit) {
            /**
             * In this case we must calculate the new (relative) position to insert the element.
             * Before reallocating, get the distance from the beginning of the array.
             **/
            difference_type d = position - begin();
            // then we resize and reallocate.
            grow();

            // calcuate the new position.
            position = begin() + d;
        }
        // insert the new element, returning the position of insertion.
        return unchecked_insert(position, v);
    }

    /**
     * Inserts a sequence of values given by the iterator range [first, last) into the
     * Vec BEFORE the element at the given position.
     **/
    template <class In> void insert(iterator position, In first, In last) {

        // get the distance between iterators (calculating it once saves us from doing it again)
        typename std::iterator_traits<In>::difference_type dist = std::distance(first, last);
        
        // get space if needed
        if (avail + dist > limit) {
            /**
             * In this case we must calculate the new (relative) position the
             * elements will be inserted from.
             * Before reallocating, get the distance from the beginning of the array.
             **/
            difference_type d = position - begin();
            /**
             * Resize and reallocate, indicating the mimimum size limit to meet
             * (current size + number of elements to add)
             * That is, keep growing the Vec until there is enough space to add 
             * each element.
             **/ 
            grow(size() + dist);
            // calcuate the new position
            position = begin() + d;
        }

        // insert the sequence of values.
        unchecked_insert(position, first, last, dist);
    }

    /**
     * Inserts a given number of copies of a give value into the Vec BEFORE the element at 
     * the given position.
     **/
    void insert(iterator position, size_type n, const T& val) {

        // get space if needed
        if (avail + n > limit) {
            /**
             * In this case we must calculate the new (relative) position the
             * elements will be inserted from.
             * Before reallocating, get the distance from the beginning of the array.
             **/
            difference_type d = position - begin();
            /**
             * Resize and reallocate, indicating the mimimum size limit to meet
             * (current size + number of elements to add)
             * That is, keep growing the Vec until there is enough space to add 
             * each element.
             **/ 
            grow(size() + n);
            // calcuate the new position
            position = begin() + d;
        }

        // insert the sequence of values.
        unchecked_insert(position, n, val);
    }

    /**
     * Replaces all the contents of the Vec with the contents of a sequence in the range of
     * iterators [first, last), thus assigining it to the Vec.
     **/
    template <class In> void assign(In first, In last) {

        // destroy the current state of the Vec, freeing the underlying array
        uncreate();

        // re-create the Vec from the contents of the sequence in iterator range [first, last)
        create(first, last);
    }

    /**
     * Removes the element pointed to by the given iterator from the Vec, returning an iterator 
     * pointing to the new location of the element that came after it.
     *
     * Note that unless erasing from the end, any iterators to elements after the deleted element 
     * will become invalid, no longer pointing to their original value, since these elements will 
     * be shifted down.
     **/
    iterator erase(iterator);

    /**
     * Removes the elements within a range of two given iterators, returning an iterator pointing
     * to the new location of the element that came after the last of these elements.
     * Note that unless erasing from the end, any iterators to elements after the deleted elements
     * will become invalid, no longer pointing to their original value, since these elements will 
     * be shifted down.
     **/
    iterator erase(iterator, iterator);

    // empties the entire Vec.
    void clear();
    

// ---- Private (class-access only) members, representing the implementation ---- 
private:

    // -------- The main member variables, iterators to different positions of the Vec --------

    // first element in the Vec
    iterator data;
    // points to (one past) the last constructed element, or equivalently, the first free space
    iterator avail;
    // points to (one past) the last allocated (but not neccessarily constructed) element in the Vec
    iterator limit; 

    // -------- Facilites for memory allocation --------

    // member object to handle memory allocation
    std::allocator<T> alloc; 

    // allocates and initializes the underlying array that will hold the elements
    // (base initializer, creating an empty Vec)
    void create();      
    // (creates a Vec of a given capacity, filling it up with a given value)                               
    void create(size_type, const T&);
    // (creates a Vec out of a sequence of values from the range of input iterators [first, last))
    template <class In> void create(In, In);

    // destroys the elements in the array and frees the memory
    void uncreate();

    // -------- Support ("helper") functions for the insert member function -------
    
    // "grows" the underlying array (i.e. reallocate memory) to allow for more elements.
    void grow();
    // (takes a given minimum threshold the resized array should meet in terms of max capacity)
    void grow(size_type);

    /**
     * Inserts a given value into the Vec BEFORE the element at the given position,
     * returning an iterator to this inserted element. It does this under the assumption that there exists
     * available, pre-allocated space for it to be initialised in (this is checked beforehand in insert)
     **/
    iterator unchecked_insert(iterator, const T&);

    /**
     * Inserts a given sequence of values in the range of given iterators into the Vec BEFORE the element 
     * at the given position, returning an iterator to this inserted element. It does this under the 
     * assumption that there exists available, pre-allocated space for it to be initialised in 
     * (this is checked beforehand in insert)
     **/
    template <class In> void unchecked_insert(iterator, In, In, difference_type);

    /**
     * Inserts a given number of of copies of a given value into into the Vec BEFORE the element 
     * at the given position, returning an iterator to this inserted element. It does this under the 
     * assumption that there exists available, pre-allocated space for it to be initialised in 
     * (this is checked beforehand in insert)
     **/
    void unchecked_insert(iterator, size_type, const T&);

    // -------- Misc. -------

    // outputs the number of allocated (but not necessary initialised) memory spaces for the Vec elements.
    difference_type size_limit() const { return limit - data; }
};

// =============================================================================================================================

// === Implementation of the undefined class methods ===

// --- Private members ---

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
    std::uninitialized_fill(data, limit, val);
}
template <class T> 
template <class In> void Vec<T>::create(In i, In j)
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
    limit = avail = std::uninitialized_copy(i, j, data);
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
    // if no minimun space is specified, we pass 0, indicating no required threshold to meet.
    grow(0);
}


template <class T> void Vec<T>::grow(size_type min_space)
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
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // return (free) the old space
    uncreate();

    // set the iterators to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T> typename Vec<T>::iterator Vec<T>::unchecked_insert(iterator position, const T& val)
{
    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * by one place. This leaves room to insert the new value into the array at the given position.
     **/

    // create a variable holding the current end of the Vec
    iterator it = avail;

    // shift values up the array, until we reach the given postiion.
    while (it != position) {
        // initialise the value at the current position using the value at the position before it
        alloc.construct(it, *(it-1));
        // destroy the value at the postiion just copied from, and more to that position.
        alloc.destroy(--it);
    }
    // finally construct an element at the position from the given value.
    alloc.construct(it, val);

    // remember to increment the pointer to the end of the Vec, since one element has just been added.
    ++avail;
    
    // return the iterator to the inserted element.
    return it;
}

template <class T>
template <class In> 
void Vec<T>::unchecked_insert(iterator position, In first, In last, difference_type dist)
{   
    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * enough so that there is room to insert the new values into the array from the given position.
     **/
    
    /**
     * Create a variable holding where the new end of the Vec will be when after the values are inserted.
     * It will be used for constructing elements at new postions.
     **/
    iterator it1 = avail + dist;
    /**
     * Create another variable holding the current end of the Vec - will be used for destructions..
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

    // remember to increase the pointer to the end of the Vec, since multiple elements have just been added.
    avail += dist;
}
/** 
 * ====================================================================
 * Demonstration of how the range version of the insert() method works.
 * ====================================================================
 * I_n = initialised elements   (considered part of the Vec to the user)
 * U_n = unconstructed elements (allocated memory, but not initialised)
 * DST = newly destroyed/unconstructed element
 * 
 * Let it1 = avail + dist  (point to the postiion that will mark the new end of Vec)
 * Assume it2 = it1 - dist (point to postiion of last element, from which we destroy down to pos.)
 * 
 *                                           |                                      | (TO ADD - 3 ELELENTS)
 * | I_1 | I_2 | I_3 | I_4 | I_5 | I_6 | I_7 | U_1 | U_2 | U_3 | U_4 | END          | {A, B, C}, END
 *               ^pos                        | ^it2             ^it1  ^limit        |  ^first    ^last
 *                                             ^avail
 *                                             <--- dist = 3 ---->
 *                  
 * | I_1 | I_2 | I_3 | I_4 | I_5 | I_6 | DST | U_1 | U_2 | I_7 | U_4 | END          // Move iterators down by 1: it1 now points to U_3
 *               ^pos                    ^it2              ^it1                     // (the position the last element will be)
 *                                       <--- dist = 3 ---->                        // Construct I_7 at position of U_3 
 *                                                                                  // Destroy the I_7 at its original position
 * 
 * | I_1 | I_2 | I_3 | I_4 | I_5 | DST | DST | U_1 | I_6 | I_7 | U_4 | END          // Move iterators down by 1: it1 now points to U_2 
 *               ^pos              ^it2              ^it1                           // Construct I_6 at position of U_2
 *                                 <--- dist = 3 ---->                              // Destroy the I_6 at its original position 
 * 
 * | I_1 | I_2 | I_3 | I_4 | DST | DST | DST | I_5 | I_6 | I_7 | U_4 | END          // Move iterators down by 1: it1 now points to U_1
 *               ^pos        ^it2              ^it1                                 // Construct I_5 at position of U_1
 *                           <--- dist = 3 ---->                                    // Destroy the I_5 at its original position
 * 
 * | I_1 | I_2 | I_3 | DST | DST | DST | I_4 | I_5 | I_6 | I_7 | U_4 | END          // Move iterators down by 1: it1 now points to the 
 *               ^pos  ^it2              ^it1                                       // original position of first shifted element (I_7)
 *                     <--- dist = 3 ---->                                          // Construct I_4 at this position
 *                                                                                  // Destroy the I_4 at its original position
 *
 * | I_1 | I_2 | DST | DST | DST | I_3 | I_4 | I_5 | I_6 | I_7 | U_4 | END          // Move iterators down by 1: it1 now points to the   
 *               ^it2              ^it1                                             // original position of second shifted element (I_6)
 *               ^pos                                                               // Construct I_3 at this position
 *               <--- dist = 3 ---->                                                // Destroy the I_3 at its original position
 * (SHIFTING LOOP ENDS HERE)                                                        // it2 = pos, so STOP SHIFTING.
 * 
 * Finally copy elements from range [first, last) starting from pos.
 *                                                             |
 * | I_1 | I_2 |  A  |  B  |  C  | I_3 | I_4 | I_5 | I_6 | I_7 | U_4 | END
 *               ^pos                                          | ^avail
 * 
 * END               
 **/

template <class T>
void Vec<T>::unchecked_insert(iterator position, size_type n, const T& val)
{   
    // (VERY SIMILAR to the range version. Only difference is that here the same value is inserted at each position)

    /**
     * The goal is to "shift" every element in the range [position, avail) up the array
     * so that there is enough room to insert the new values into the array from the given position.
     **/
    
    /**
     * Create a variable holding where the new end of the Vec will be when after the values are inserted.
     * It will be used for constructing elements at new postions.
     **/
    iterator it1 = avail + n;

    /**
     * Create another variable holding the current end of the Vec - will be used for destructions.
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

    // finally, starting from the given position, construct n elements from the given value.
    std::uninitialized_fill(position, position + n, val);

    // remember to increase the pointer to the end of the Vec, since n elements have has just been added.
    avail += n;
}

// --- Public members ---

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
 
template <class T> typename Vec<T>::iterator Vec<T>::erase(iterator position)
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

template <class T> typename Vec<T>::iterator Vec<T>::erase(iterator b, iterator e)
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
    
    // shift values up the array, until we reach the end of the Vec.
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
/** 
 * ====================================================================
 * Demonstration of how the range version of the erase() method works.
 * ====================================================================
 * I_n = initialised elements   (considered part of the Vec to the user)
 * U_n = unconstructed elements (allocated memory, but not initialised)
 * DST = newly destroyed/unconstructed element
 * 
 * Erasing elements in the iterator range [b, e)
 * Let it1 = avail + dist  (point to the postiion that will mark the new end of Vec)
 * Assume it2 = it1 - dist (point to postiion of last element, from which we destroy down to pos.)
 * 
 *                                                       |               
 * | I_1 | I_2 | I_3 | I_4 | I_5 | I_6 | I_7 | I_8 | I_9 | U_1 | U_2 | END          // Erasing elements in the iterator range [b, e)...
 *               ^b                ^e                    | ^avail      ^limit       
 * 
 * 
 * | I_1 | I_2 | DST | DST | DST | I_6 | I_7 | I_8 | I_9 | U_1 | U_2 | END          // Destroy the elements in [b, e)
 *               ^it1              ^it2                    ^avail      ^limit       // Set it1 = b, it2 = e
 *                                                                                  
 * (SHIFTING LOOP STARTS HERE)                                                      
 * 
 * | I_1 | I_2 | I_6 | DST | DST | DST | I_7 | I_8 | I_9 | U_1 | U_2 | END          // Construct I_6 at it1
 *                     ^it1              ^it2              ^avail      ^limit       // Destroy the I_6 at it2
 *                                                                                  // Shift iterators up by 1: it2 now points to I_7
 * 
 * | I_1 | I_2 | I_6 | I_7 | DST | DST | DST | I_8 | I_9 | U_1 | U_2 | END          // Construct I_7 at it1
 *                           ^it1              ^it2        ^avail      ^limit       // Destroy the I_7 at it2
 *                                                                                  // Shift iterators up by 1: it2 now points to I_8
 * 
 * | I_1 | I_2 | I_6 | I_7 | I_8 | DST | DST | DST | I_9 | U_1 | U_2 | END          // Construct I_8 at it1 
 *                                 ^it1              ^it2  ^avail      ^limit       // Destroy the I_8 at it2
 *                                                                                  // Shift iterators up by 1: it2 now points to I_9
 *                                                                                  
 * | I_1 | I_2 | I_6 | I_7 | I_8 | I_9 | DST | DST | DST | U_1 | U_2 | END          // Construct I_9 at it1    
 *                                       ^it1              ^it2        ^limit       // Destroy the I_9 at it2
 *                                                         ^avail                   // Shift iterators up by 1: it2 now points to I_9
 *                                       <--- dist = 3 ---->                        // it2 = avail, so STOP SHIFTING.
 * (SHIFTING LOOP ENDS HERE)                                                       
 * 
 * Set avail to the position of it1 - the left-most position with a destoyed element
 *                                     |
 * | I_1 | I_2 | I_6 | I_7 | I_8 | I_9 | DST | DST | DST | U_1 | U_2 | END         
 *                                     | ^avail                        ^limit 
 * 
 * END               
 **/

template <class T> void Vec<T>::clear()
{   
    // destroy each element of the Vec, from the last back down to the first.
    while (avail != data) {
        alloc.destroy(avail - 1);
        // continue to decrement avail until it reaches the start position of the Vec, indicating that all ele clear.
        --avail;
    }
}

/**
 * ==========================================================
 * ALLOCATOR OBJECTS AND THEIR USEFULNESS
 * ==========================================================
 * An std::allocator<T> object is used to manage memory at a very low level during runtime.
 * 
 * It is used to allocate memory for an object (or an array of objects) of type T to utilise, but WITHOUT 
 * also constructing/initialising an object at that memory location. This has to be done separately.
 * It may also be used to destroy an object at a memory location, and deallocate (free) the memory, 
 * both of which must also be done separately.
 * 
 * This is in contrast with allocating/deallocating memory through the 'new' and 'delete' operators,
 * which do these in a single step.
 *
 * For our Vec class which utilises a dynamic array to hold the elements, the allocator object allows
 * us to only construct elements as they are added to the Vec. For memory locations in the array yet
 * to be used, we can construct them later if more elements need to be added.
 * 
 * Otherwise, with the 'new' operator, each part of the array would be constructed twice: 
 * once immediately after allocation, and again when we actually want to use the position to add an
 * element to the Vec. This is not only inefficient, but redundant.
 * 
 * Therefore allocator objects not only provide a greater degree of flexibility in regards to dynamic memory
 * management, but also more efficiency in terms of performance. 
 * 
 **/

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

/**
 * =================================================
 * DIFFERENCES BETWEEN INITIALISATION AND ASSIGNMENT
 * =================================================
 * Initialisation: Involves setting up a NEW object, allocating memory for it to use.
 *                 Will always involve calling an object's constructor, whether implicitly or explicitly.
 * 
 * Assignment:     Involves modifying a PRE-EXISTING object to match another one, destroying the previous state
 *                 and deallocating memory when necessary.  
 *                 Will always involve the '=' operator for an ALREADY initialised object, which may defined
 *                 in a class as the member function 'operator=', and may be overloaded to allow assignment
 *                 to different types of objects. 
 * 
 *                 A special case of is when the value to be assigned is a constant refererence to an object 
 *                 of the same type. This particular instance of the '=' operator is called the 
 *                 "assignment operator". If the user does not define one, the compiler will do so 
 *                 automatically.
 *                  
 *                 If no appropriate 'operator=' overload exists when doing assignment, the compiler will call 
 *                 a constructor which takes a single constant of matching type if it exists, effectively 
 *                 converting the value on the right to the same type as the object on the left, 
 *                 then calling the assignment operator to complete the operation.
 *                 
 * === IMPORTANT NOTE ===
 * When the '=' operator is used to give an initial value immediately to a newly declared variable,
 * this is NOT assignment, but initialisation, calling the object's copy constructor if the value is the same type.
 * In this instance, '=' does NOT refer to the assignment operator, but the general '=' operator.
 * 
 * If the value is of a different type, then an approprate constructor that can take it as a single argument is
 * called if it exists. This behavior can be prevented by qualifying the constructor with the 'explicit' keyword
 * so that it must be written out explicitly if it is to be called.
 * 
 * === EXAMPLE SHOWCASING THE DIFFERENCES IN USE OF THE '=' OPERATOR ===
 * 
 *                      std::string str = "Hello World!";
 *             
 * is initialisation, implicitly calling a constructor that takes a char*.
 * 
 *                      std::string str; str = "Hello World!";
 *        
 * is first initialisation (using default constructor), followed by assignment (using operator= that takes a char*).
 * This is less efficient than the fist method (and also redundant).
 * 
 *                      Vec<double> v1(10); Vec<double> v2 = v1
 *                  
 * is initialisation of one Vec<double> object, explicitly calling a constructor that can take a single integer,
 * followed by initialisation of another Vec<double> object using the first one, implicitly calling the copy constructor.
 * 
 *                      Vec<double> v1; v1 = Vec<double>(10)
 * 
 * is initialisation of one Vec<double> object, using the default constructor,
 * followed by applying THE assignment operator on that object to another (temporary) object newly initialised by a constructor
 * taking a single integer (we are not allowed to write for the assignment v1 = 10 (which does exactly the same) because 
 * the constructor is qualified with the 'explicit' keyword). It would be more efficient to simply write Vec<double> v1(10);
 **/
#endif