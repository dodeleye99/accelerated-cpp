#ifndef GUARD_Vec_h
#define GUARD_Vec_h

#include <algorithm>    // std::max;
#include <cstddef>      // std::ptrdiff_t;
#include <memory>       // std::allocate<T>, std::uniuninitialized_copy, std::uninitialized_fill
#include <cstddef>      // std::ptrdiff_t and std::size_t

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

    // Indexing operator, returning the pointer of an element at a given position.
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
    size_type size_limit() const { return limit - data; }
};

#endif

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
 *                 "assignment operator".
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
 * is initialisation of one Vec<double> object, using the default constructior,
 * followed by applying THE assignment operator on that object to another (temporary) object newly initialised by a constructor
 * taking a single integer. It would be more efficient to simply write Vec<double> v1(10);
 **/

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