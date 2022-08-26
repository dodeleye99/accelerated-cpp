#ifndef GUARD_Vec_h
#define GUARD_Vec_h

#include <algorithm>    // std::max;
#include <cstddef>      // std::ptrdiff_t and std::size_t
#include <memory>       // std::allocate<T>, std::uniuninitialized_copy, std::uninitialized_fill

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

    // outputs the number of elements in the Vec
    size_type size() const { return avail - data; }

    // outputs an iterator to the first element of the Vec
    iterator begin() { return data; }
    // (read-only iterator)
    const_iterator begin() const { return data; }

    // outputs an iterator to the end of the Vec (one-past the last element)
    iterator end() { return avail;}
    // (read-only iterator)
    const_iterator end() const {return avail; }

    // add an element to the end of the Vec.
    void push_back(const T& t) {
        // get space if needed
        if (avail == limit) {
            grow();
        }
        // append the new element
        unchecked_append(t);
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

    // empties the entire Vec.
    void clear();

    // a predicate for whether the Vec is empty (no elements).
    bool empty() const { return data == avail; }
    

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
    // (creates a Vec of values given by a sequence bound by two iterators)    
    void create(const_iterator, const_iterator);

    // destroys the elements in the array and frees the memory
    void uncreate();

    // -------- Support ("helper") functions for the push_back member function -------
    
    // "grows" the underlying array (i.e. reallocate memory) to allow for more elements.
    void grow();

    /**
     * adds an element to the end of the Vec, under the assumption that there exists available, pre-allocated 
     * space for it to be initialised in (this is checked beforehand in push_back).
     **/ 
    void unchecked_append(const T&);

    // -------- Misc. -------

    // outputs the number of allocated (but not necessary initialised) memory spaces for the Vec elements.
    difference_type size_limit() const { return limit - data; }
};

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
    /**
     * While "growing", allocate twice as much space as currently in use
     * (if empty, then allocate only a single space)
     **/
    size_type new_size = std::max(2 * size_limit(), ptrdiff_t(1));

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

template <class T> void Vec<T>::unchecked_append(const T& val)
{
    /**
     * At the end of the sequence of constructed elements, initialise a single element as a copy of val.
     * Then increment avail to point to the next free (pre-allocated), constructable space.  
     **/
    alloc.construct(avail++, val);
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

/**
 * ==============================================
 * Demonstration of how the erase() method works.
 * ==============================================
 * I_n = initialised elements   (considered part of the Vec to the user)
 * U_n = unconstructed elements (allocated memory, but not initialised)
 * DST = newly destroyed/unconstructed element
 * 
 * (I_1, I_2, I_3, TO_DELETE, I_5, I_6, U_1, U_2, U_3)      // start at element to delete
 *  ^data          ^it                  ^avail    ^limit
 * 
 * (I_1, I_2, I_3, DST, I_5, I_6, U_1, U_2, U_3)            // destroy the element, then go to next (I_5)
 *  ^data               ^it       ^avail    ^limit
 * 
 * (I_1, I_2, I_3, I_5, I_5, I_6, U_1, U_2, U_3)            // construct prev. element from current one (I_5)
 *  ^data               ^it       ^avail    ^limit
 * 
 * (I_1, I_2, I_3, I_5, DST, I_6, U_1, U_2, U_3)            // destroy the element (I_5), then go to next (I_6)
 *  ^data                    ^it  ^avail    ^limit
 * 
 * (I_1, I_2, I_3, I_5, I_6, I_6, U_1, U_2, U_3)            // construct prev. element from current one (I_6) 
 *  ^data                    ^it  ^avail    ^limit
 * 
 * (I_1, I_2, I_3, I_5, I_6, DST, U_1, U_2, U_3)            // destroy the element (I_6), then go to next (U_1)
 *  ^data                         ^avail    ^limit          // reached avail, marking the end of original set           
 *                                ^it                       // of unconstructed elements, so stop.
 * 
 * (I_1, I_2, I_3, I_5, I_6, DST, U_1, U_2, U_3)            // shift avail down to point to DST, since this
 *  ^data                    ^avail    ^limit               // is the new beginning of the unstonstructed sequence.           
 *                                  
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
