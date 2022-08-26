#ifndef GUARD_Str_h
#define GUARD_Str_h

#include <algorithm>    // std::copy, std::min
#include <cstring>      // std::strlen
#include <iostream>     // std::istream, std::ostream
#include <iterator>     // std::distance, std::iterator_traits<It>
#include <memory>       // std::allocate<T>, std::uniuninitialized_copy, std::uninitialized_fill


/**
 * A simplified version of the std::string class. used to implement strings.
 **/
class Str {
    /**
     * Use the 'friend' keyword to give the operator>>() function (only the one that takes istream and Str)
     * and the getline() function (taking an istream, Str and chars) access rights to private members of a 
     * Str object (particularly the 'dta' member variable). 
     * 
     * This is more optimal than making members public, since it enables us to still hide the implementation
     * details from the user, while also preventing them from accessing and modifying them.
     */
    friend std::istream& operator>>(std::istream&, Str&);
    friend std::istream& getline(std::istream&, Str&, char);
public:

    // --------------- Type definitions ---------------

    // type used to represent the type of the elements stored
    typedef char value_type;
     // type used for defining references to an object of value_type
    typedef char& reference;
    // constant reference type used for read-only access  
    typedef const char& const_reference;                  

    // type used to represent size of the Str
    typedef std::size_t size_type;
    // type used to represent distance between iterators (by subtraction)
    typedef std::ptrdiff_t difference_type;
    
    // type used for iterating over elements of the contanier.
    typedef char* iterator;
    // constant iterator type used for read-only access                  
    typedef const char* const_iterator;            

    // --------------- Constructors ---------------
    
    
    // default constructor: create an empty Str
    Str() 
    { create(); /*allocate_c();*/ }

    // copy constructor: create a Str from another Str
    Str(const Str& s)/*: dta(s.dta)*/ 
    { create(s.begin(), s.end()); /*allocate_c();*/ }

    // fill constructor: create a Str containing n copies of c
    Str(size_type n, char c)/*: dta(n, c)*/
    {  create(n, c); /*allocate_c();*/ }

    // range constructor: create a Str from the range denoted by iterators b and e
    template <class In> Str(In b, In e)/*: dta(b, e)*/ 
    { create(b, e); /* allocate_c(); */ }

    /**
     * Creates a Str from null-terminated array of char (i.e. a string literal).
     * 
     * This constructor also acts as a user-defined conversion from a const char* to a Str,
     * used by the compiler whenever it is needed.
     * 
     * As a result, operator+= and operator+ will work with const char*
     * arguments if the compiler can detect their overloads.
     **/
    Str(const char* cp) {
        create(cp, cp + std::strlen(cp));
        /* std::copy(cp, cp + std::strlen(cp), std::back_inserter(dta));
        allocate_c(); */
    }

    // --------------- Destructor ---------------
    ~Str() { 
        uncreate();
        /* // we only need to deallocate the array pointed to by member c. The Vec<char> object will deallocate itself.
        delete[] c;  */
    }

    // --------------- Operators ---------------
    
    // the assignment operator: change state of the Str so that it matches the state of another Str, while independent.
    Str& operator=(const Str& rhs){

        // check for self-assignment, in which case do nothing.
        if(&rhs != this) {
            // free the array in the left hand side
            uncreate();

            // copy elements from the right-hand side to the left-hand side (this object)
            create(rhs.begin(), rhs.end());
        }
        // ensure to return the modified object.
        return *this;
        /* dta = s.dta;
        reallocate_c();
        return *this; */
    }

    // indexing operator: return a reference to the char at a given position, allowing it to be modified.
    char& operator[](size_type i) {
        reallocate_c();
        return dta[i]; 
    }
    // (for read-only)
    const char& operator[](size_type i) const { return dta[i]; }

    // concatenation operator: join the characters of a given Str to the end of this Str.
    Str& operator+=(const Str& s) {

        // copy the characters of the right operand to the end of characters of the left operand (this Str)
        insert(avail, s.begin(), s.end());

        // the Str has been changed, so reallocate the chararacter array given by the member c.
        reallocate_c(); // redundant, done by insert();

        // return a refrence to the left operand (this Str), giving the final result.
        return *this;
    }
    // (concatenate the contents of a given c-string to the end of this Str)
    Str& operator+=(const char* s) {
        // copy the characters of the right operand to the end of characters of the left operand (this Str)
        insert(avail, s, s + std::strlen(s));
        reallocate_c(); // redundant, done by insert();
        return *this;
    }
    // (concatenate a single character to the end of this Str)
    Str& operator+=(char c) {
        // simply do a push_back() operation to concatenate the character
        push_back(c);
        reallocate_c(); // redundant - done by push_back();
        return *this;
    }
    
    /**
     * Converts Str object to bool, allowing it to implicitly be used as a condition. 
     * The bool value is determined by whether the Str being empty (no characters).
     * If it is empty, the value is false. Oterwise, the value is true.
     **/
    operator bool() const { return !empty(); }

    // --------------- Other member functions ---------------

    // ---- Iterators ----
    
    // outputs an iterator to the first element of the Str
    iterator begin() { 
        reallocate_c();
        return dta; 
    }
    // (read-only iterator)
    const_iterator begin() const { return dta; }

    // outputs an iterator to the end of the Str (one-past the last element)
    iterator end() { 
        reallocate_c();
        return avail;
    }
    // (read-only iterator)
    const_iterator end() const {return avail; }

    // ---- Capacity functions ----

    /**
     * Outputs the number of chars that make up the Str
     * Note that null characters '\0' are counted too.
     **/
    size_type size() const { return avail - dta; }

    /**
     * A predicate for whether the Str is empty (no elements).
     * Note that a Str of null characters '\0' does not count as empty.
     **/
    bool empty() const { return dta == avail; }

    /**
     * Modifies the Str such that the number of elements stored in it is changed
     * to match a given size.
     * 
     * If the given size is greater than the current size, the Str is filled up
     * with new elements, initialised by a given value (null-characters if none specified), 
     * to reach the required size. 
     * 
     * If the given size is less than the current size, then elements 
     * from the end of the Str are erased to make the Str have the required
     * size.
     * 
     * If the given size matches the current size, nothing happens.
     **/
    void resize(size_type n, char c = '\0') {
        
        // record the current size of the Str
        size_type sz = size();

        // if above the given size, erase enough elements from the end.
        if(sz > n) {
            erase(avail - (sz - n), avail);
        }

        // if below the given size, insert enough copies of the given value to the end.
        else if(sz < n){
            insert(avail, n - sz, c);
        }
        else{
            // non-const function called - thus do char-array reallocation
            reallocate_c(); 
        }

        // // guarantee char-array reallocation only if the size actually changed.
        // reallocate_c(n == sz);  // REDUNDANT
    }

    // ---- Modifiers ----

    // inserts a given character into the Str BEFORE the element at the given position 
    iterator insert(iterator position, char c){ 

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
        // insert the new element, getting the position of insertion.
        iterator ret =  unchecked_insert(position, c);

        // size changed - must reallocate char array.
        reallocate_c(false);

        return ret;

        /* iterator ret = dta.insert(position, c);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret; */
    }

    /**
     * Inserts a sequence of (assumed char-convertable) values given by the iterator range [first, last) into the
     * Str BEFORE the element at the given position.
     **/
    template<class In> void insert(iterator position, In first, In last) {

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
             * That is, keep growing the Str until there is enough space to add 
             * each element.
             **/ 
            grow(size() + dist);
            // calcuate the new position
            position = begin() + d;
        }

        // insert the sequence of values.
        unchecked_insert(position, first, last, dist);

        // (assumed) size changed - must reallocate char array.
        reallocate_c(false); 

        /* dta.insert(position, first, last);
        // (assumed) size changed - must reallocate char array.
        reallocate_c(false); */
    }

    /**
     * Inserts a given number of copies of a given character into the
     * Str BEFORE the element at the given position.
     **/
    void insert(iterator position, size_type n, char c) {

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
             * That is, keep growing the Str until there is enough space to add 
             * each element.
             **/ 
            grow(size() + n);
            // calcuate the new position
            position = begin() + d;
        }

        // insert the sequence of values.
        unchecked_insert(position, n, c);

        // (assumed) size changed - must reallocate char array.
        reallocate_c(false);

        /* dta.insert(position, n, c);
        // (assumed)size changed - must reallocate char array.
        reallocate_c(false); */
    }

    // adds a single character to the end of the Str.
    void push_back(char c) {
        // this is equivalent to inserting an element at the end of the Str.
        insert(avail, c);
    }

    /**
     * Replaces all the contents of the Str with the contents of a sequence (of assumed char-convertable values) 
     * in the range of iterators [first, last), thus assigining it to the Str.
     **/
    template <class In> void assign(In first, In last) {

        // destroy the current state of the Str, freeing the underlying array
        uncreate();

        // re-create the Str from the contents of the sequence in iterator range [first, last)
        create(first, last);
    }

    /**
     * Removes the character pointed to by the given iterator from the Str, returning an iterator pointing
     * to the new location of the character that came after it.
     * Note that unless erasing from the end, any iterators to characters after the deleted character 
     * will become invalid, no longer pointing to their original value, since these character will 
     * be shifted down.
     **/
    iterator erase(iterator position){

        iterator ret = erase_chars(position);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret;
        /* iterator ret = dta.erase(position);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret; */
    }

    /**
     * Removes the characters within a range of two given iterators, returning an iterator pointing
     * to the new location of the character that came after the last of these characters.
     * Note that unless erasing from the end, any iterators to characters after the deleted characterss 
     * will become invalid, no longer pointing to their original value, since these character will 
     * be shifted down.
     **/
    iterator erase(iterator first, iterator last){

        iterator ret = erase_chars(first, last);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret;
        /* iterator ret = dta.erase(first, last);
        // (assumed) size changed - must reallocate char array.
        reallocate_c(false);
        return ret; */
    }

    // removes every character of the Str.
    void clear() { 
        // simply erase every element.
        erase(begin(), end());
    }

    // ---- Character array conversion functions ----
    
    /**
    * Returns a pointer to a null-terminated (last element '\0') char array (known as a C-string) consisting
    * of the same sequence of characters as the Str object.
    *
    * Note that the data in the array will remain valid until the Str object is later modified by some
    * operation performed on it. It must also not be destroyed by the user. Finally it will be deallocated once
    * the Str object is destroyed, so it must not leave the same scope as the original Str (unless dynamic).
    **/
    const char* c_str() const { return char_array(true); }

    /**
     * Returns a pointer to a char array consisting of the same sequence of characters as the Str object,
     * as with c_str(). However, unlike it, the array is NOT GUARANTEED to be null-terminated 
     * (i.e. it is not ensured to end with '\0').
     **/
    const char* data() const { return char_array(false); }

    /**
     * Recieves a pointer to an existing or newly (dynamically) allocated char array, and copies a 
     * sub-Str of length n from the Str obbject, marked by the index range [pos, pos + n),
     * to the array. It then returns the number of characters that were copied. If no starting position is 
     * given, then the sub-Str begins from the start of the Str.
     * 
     * The user will be responsible for making sure that the array they want to use is large enough to
     * hold all the characters they would like to copy into it.
     * 
     * If the sub-Str they are copying from goes beyond the range of the entire Str, then as may 
     * characters as possible are copied (i.e. up to the last element of the Str).
     * 
     **/
    size_t copy(char* p, size_t n, size_t pos=0) const {

        // define an iterator pointing to the character at the index marked by pos.
        const char* b = begin() + pos;
        // define an iterator n places afterward (or to the end of the Str if b+n goes past the end).
        const char* e = b + std::min(n, size() - pos);

        // copy the sub-Str marked by range [b, e) into the array from its front.
        std::copy(b, e, p);

        // finally output the number of characters that were copied into the array.
        return b - e;
    }

private:

    // -------- The main member variables, iterators to different positions of the Str --------

    // points to the first character of the Str
    iterator dta;
    // points to (one past) the last constructed element, or equivalently, the first free space
    iterator avail;
    // points to (one past) the last allocated (but not neccessarily constructed) element in the Str
    iterator limit; 

    // -------- Facilites for memory allocation --------

    // member object to handle memory allocation
    std::allocator<char> alloc;

    // allocates and initializes the underlying array that will hold the elements
    // (base initializer, creating an empty Str)
    void create();
    // (creates a Str of a given capacity, filling it up with a given value)                               
    void create(size_type, const char&);

    // (creates a Str out of a sequence of values from the range of input iterators [first, last))
    template <class In> void create(In, In);

    // destroys the elements in the array and frees the memory
    void uncreate();

    // -------- Support ("helper") functions for the insert member function -------
    
    // "grows" the underlying array (i.e. reallocate memory) to allow for more elements.
    void grow();
    // (takes a given minimum threshold the resized array should meet in terms of max capacity)
    void grow(size_type);

    /**
     * Inserts a given value into the Str BEFORE the element at the given position,
     * returning an iterator to this inserted element. It does this under the assumption that there exists
     * available, pre-allocated space for it to be initialised in (this is checked beforehand in insert)
     **/
    iterator unchecked_insert(iterator, const char&);

    /**
     * Inserts a given sequence of values in the range of given iterators into the Str BEFORE the element 
     * at the given position, returning an iterator to this inserted element. It does this under the 
     * assumption that there exists available, pre-allocated space for it to be initialised in 
     * (this is checked beforehand in insert)
     **/
    template <class In> void unchecked_insert(iterator, In, In, difference_type);

    /**
     * Inserts a given number of of copies of a given value into into the Str BEFORE the element 
     * at the given position, returning an iterator to this inserted element. It does this under the 
     * assumption that there exists available, pre-allocated space for it to be initialised in 
     * (this is checked beforehand in insert)
     **/
    void unchecked_insert(iterator, size_type, const char&);

    // -------- Support ("helper") functions for the erase member function -------
    
    /**
     * Implements the erase() member function that removes a single character from the Str, at the
     * position indicated by a given iterator, returning an iterator pointing to the new location 
     * of the character that came after it.
     **/
    iterator erase_chars(iterator);
    /**
     * Implements the erase() member function that removes characters from the Str in the range
     * of two given iterators, returning an iterator pointing to the new location of the element 
     * that came after the last of these characters.
     **/
    iterator erase_chars(iterator, iterator);

    // -------- Facilites for constructing and destroying the stored character array --------

    /**
     * Represents a pointer to a character array holding the same char values as those in dta 
     * used to implement the Str.
     * 
     * Its purpose is to be used by the c_str() and data() member functions to enable the user 
     * to explicitly convert the Str to a char*, since there are potential dangers with an
     * implicit/automatic conversion (e.g. memory leaks due to inability to deallocate array 
     * if the pointer is never retrieved).
     * 
     * Even the conversion functions must still be used carefully, since the user
     * obtains from the them the same (but a read-only) array that this member points to:
     * 
     * 1)   If the user deletes the array using the pointer they receive, this pointer will 
     *      point to space that has been deallocated, causing potential errors if used.
     *      Therefore the pointer they receive must not ever be used to destroy the array.
     * 
     * 2)   The array is updated only when one of these two functions are called, reflecting
     *      the state of the Str only at these points in time. It will be invalidated if the 
     *      original Str object is later modified by some operation performed on it.
     * 
     * 3)   The lifetime of the array is tied to the lifetime of the Str, and therefore one 
     *      should not store a pointer to it for long-term use - it should ideally be used 
     *      immediately after being called (as a temporary object).
     * 
     * The actual array starts at the second element, with the first element used as a 
     * flag (c[0] == '\0') to indicate whether it has been constructed with any of the 
     * two conversion functions since its last (re)allocation, to prevent redundancy and 
     * thus improve efficiency. Thus the user will recieve a pointer one-past the first element.
     **/
    char* c;
    
    /**
     * Dynamically allocates space for a character array to be pointed to by data member c,
     * to be used as a char* representation of the Str object.
     **/
    void allocate_c();

    // destroys the character array pointed to by data member c, freeing the memory.
    void deallocate_c();
    
    /**
     * Reallocates the character array pointed to by data member c, in cases where the Str object
     * may have been modified. Its original values will be lost - the actual setup take places in
     * c_str() or data(), the only points at which the array is needed.
     * 
     * For efficiency purposes, it does nothing if the array has yet to be set up since its last 
     * (re)allocation, unless the given bool value is false, indicating to do reallocation regardless.
     * 
     * If no argument is passed, it does the check by default.
     **/
    void reallocate_c(bool);
    // (version that takes no argument - does the check by default)
    void reallocate_c();

    /**
     * Implements both c_str() and data(), which only differ by
     * the fact that the former gives an array that is null-terminated, while
     * the latter does not (hence the bool parameter 'nullled').
     **/
    const char* char_array(bool nulled) const {

        /**
         * If the first element ('init flag') is a true bool value, then the array is already set up. 
         * in this case, return the character array (one past the 'init flag').
         **/
        if(*c) {
            return c + 1;
        }

        // initialise a new pointer pointing to the same array.
        char* p = c;

        /**
         * Set the first element ('init flag') to ANY non-null character, to inidicate that
         * the array is (about to be) set up. Then move to the next element, the point at
         * which the character array really begins.
         **/
        p++[0] = '0';

        // copy the elements of the Str object into this array.
        std::copy(begin(), end(), p);

        // if the array is to be null-terminated, set the final element to be a terminating null-character.
        if(nulled) {
            p[size()] = '\0';
        }

        // finally output the pointer to the array.
        return p;
    }

    // -------- Misc. -------

    // outputs the number of allocated (but not necessary initialised) memory spaces for the Str elements.
    difference_type size_limit() const { return limit - dta; }
};
// ========================================================================================================

// ------------------- Non-member operators -------------------

// ---- I/O operators ----

// reads input from an input stream, storing what was read in a given Str
std::istream& operator>>(std::istream&, Str&);

// writes the value of a given Str to an onput stream
std::ostream& operator<<(std::ostream&, const Str&);

// Reads characters from an istream, loading them into a Str, until a delimiter character is found.
std::istream& getline(std::istream&, Str&, char);
// (If no delimiter is specified, the newline character ('\n') will automatically used as one)
std::istream& getline(std::istream&, Str&);

// ---- Concatenation operators ----

/**
 * Concatenates two Strs, producing a new Str made up of the characters of the first Str operand
 * followed by those of the second Str operand.
 **/
Str operator+(const Str&, const Str&);

// concatenation with a chararacter array (to prevent the need for automatic conversion)
Str operator+(const char*, const Str&);
Str operator+(const Str&, const char*);

// concatenation with a single character
Str operator+(char, const Str&);
Str operator+(const Str&, char);

// ------ Relational operators - comparing strings lexograhically ------
bool operator<(const Str&, const Str&);
bool operator>(const Str&, const Str&);
bool operator<=(const Str&, const Str&);
bool operator>=(const Str&, const Str&);

// Equality operator - to determine whether two strings match.
bool operator==(const Str&, const Str&);
// Inquality operator - to determine whether two strings do not match.
bool operator!=(const Str&, const Str&);

#endif