#ifndef GUARD_Str_h
#define GUARD_Str_h

#include <algorithm>    // std::copy, std::min
#include <cstring>      // std::strlen
#include <iostream>     // std::istream, std::ostream
#include <iterator>     // std::back_inserter

#include "Vec.h"


/**
 * A simplified version of the std::string class. used to implement strings.
 * In reality, it is an "extension" of  Vec<char>, which is a particular instance of the Vec template class, 
 * with extra operators specific for strings, such as concatenation, input and output, and conversion to
 * and from char arrays.
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
    
    // type used to represent size of the Str
    typedef Vec<char>::size_type size_type;
    // type used for iterating over elements of the contanier.
    typedef Vec<char>::iterator iterator;
    // constant iterator type used for read-only access                  
    typedef Vec<char>::const_iterator const_iterator;            


    // --------------- Constructors ---------------
    
    
    // default constructor: create an empty Str
    Str() { allocate_c(); }

    // copy constructor: create a Str from another Str
    Str(const Str& s): dta(s.dta) { allocate_c(); }

    // fill constructor: create a Str containing n copies of c
    Str(size_type n, char c): dta(n, c){ allocate_c(); }

    // range constructor: create a Str from the range denoted by iterators b and e
    template <class In> Str(In b, In e): dta(b, e) { allocate_c(); }

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
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(dta));
        allocate_c();
    }

    // --------------- Destructor ---------------
    ~Str() { 
        // we only need to deallocate the array pointed to by member c. The Vec<char> object will deallocate itself.
        delete[] c; 
    }

    // --------------- Operators ---------------
    
    // the assignment operator: change state of the Str so that it matches the state of another Str, while independent.
    Str& operator=(const Str& s){
        
        // check for self-assignment, in which case do nothing.
        if(&s != this) {
            dta = s.dta;
            reallocate_c();
        }
        return *this;
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
        // copy the characters of the right operand to those of the left operand (this Str)
        std::copy(s.dta.begin(), s.dta.end(), std::back_inserter(dta));

        // the Str has been changed, so reallocate the chararacter array given by the member c.
        reallocate_c(false);

        // return a refrence to the left operand (this Str), giving the final result.
        return *this;
    }
    // (concatenate the contents of a given c-string to the end of this Str)
    Str& operator+=(const char* s) {
        std::copy(s, s +  std::strlen(s), std::back_inserter(dta));
        reallocate_c(false);
        return *this;
    }
    // (concatenate a single character to the end of this Str)
    Str& operator+=(char c) {
        // simply do a push_back() operation to concatenate the character
        dta.push_back(c);
        reallocate_c(false);
        return *this;
    }
    
    /**
     * Converts Str object to bool, allowing it to implicitly be used as a condition. 
     * The bool value is determined by whether the Str being empty (no characters).
     * If it is empty, the value is false. Oterwise, the value is true.
     **/
    operator bool() const { return !dta.empty(); }

    // --------------- Other member functions ---------------

    // ---- Iterators ----
    
    // outputs an iterator to the first element of the Str
    iterator begin() {
        reallocate_c();
        return dta.begin(); 
    }
    // (read-only iterator)
    const_iterator begin() const { return dta.begin(); }

    // outputs an iterator to the end of the Str (one-past the last element)
    iterator end() {
        reallocate_c();
        return dta.end();
    }
    // (read-only iterator)
    const_iterator end() const {return dta.end(); }

    // ---- Capacity functions ----

    // outputs the number of chars that make up the Str
    size_type size() const { return dta.size(); }

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
    void resize(size_type n, char c = '\0') {
        
        // record the current size of the Vec
        size_type sz = size();

        // resize the Vec
        dta.resize(n, c);
        
        // guarantee char-array reallocation only if the size actually changed.
        reallocate_c(n == sz);
    }

    // ---- Modifiers ----

    // inserts a given character into the Str BEFORE the element at the given position 
    iterator insert(iterator position, char c){ 
        iterator ret = dta.insert(position, c);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret;
    }

    /**
     * Inserts a sequence of (assumed char-convertable) values given by the iterator range [first, last) into the
     * Str BEFORE the element at the given position.
     **/
    template<class In> void insert(iterator position, In first, In last) {
        dta.insert(position, first, last);
        // (assumed) size changed - must reallocate char array.
        reallocate_c(false);
    }

    /**
     * Inserts a given number of copies of a given character into the
     * Str BEFORE the element at the given position.
     **/
    void insert(iterator position, size_type n, char c) {
        dta.insert(position, n, c);
        // (assumed)size changed - must reallocate char array.
        reallocate_c(false);
    }

    /**
     * Removes the character pointed to by the given iterator from the Str, returning an iterator pointing
     * to the new location of the character that came after it.
     * Note that unless erasing from the end, any iterators to characters after the deleted character 
     * will become invalid, no longer pointing to their original value, since these character will 
     * be shifted down.
     **/
    iterator erase(iterator position){ 
        iterator ret = dta.erase(position);
        // size changed - must reallocate char array.
        reallocate_c(false);
        return ret;
    }

    /**
     * Removes the characters within a range of two given iterators, returning an iterator pointing
     * to the new location of the character that came after the last of these characters.
     * Note that unless erasing from the end, any iterators to characters after the deleted characterss 
     * will become invalid, no longer pointing to their original value, since these character will 
     * be shifted down.
     **/
    iterator erase(iterator first, iterator last){
        iterator ret = dta.erase(first, last);
        // (assumed) size changed - must reallocate char array.
        reallocate_c(false);
        return ret;
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
        const char* b = dta.begin() + pos;
        // define an iterator n places afterward (or to the end of the Str if b+n goes past the end).
        const char* e = b + std::min(n, dta.size() - pos);

        // copy the sub-Str marked by range [b, e) into the array from its front.
        std::copy(b, e, p);

        // finally output the number of characters that were copied into the array.
        return b - e;
    }

private:
    /**
     * Represents the underlying data structure used to implement 
     * the Str: a Vec of chars.
     **/
    Vec<char> dta;

    /**
     * Represents a pointer to a character array holding the same char values as those in the 
     * Vec<char> representing the Str.
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

    // -------- Facilites for constructing and destroying the stored character array --------

    /**
     * Dynamically allocates space for a character array to be pointed to by data member c,
     * to be used as a char* representation of the Str object.
     **/
    void allocate_c()
    {   
        /**
         * Allocate enough space for all the characters making up the Str object, with two extra spaces
         * for an 'init flag' and a terminating null-character (for c_str()).
         **/
        c = new char[size() + 2];

        // Set the 'flag' element to the null character, indicating that the array is yet to be set up.
        c[0] = '\0';
    }
        
    /**
     * Reallocates the character array pointed to by data member c, in cases where the Str object
     * may have been modified. Its original values will be lost - the actual setup take places in
     * c_str() or data(), the only points at which the array is needed.
     * 
     * For efficiency purposes, it does nothing if the array has yet to be set up since its last 
     * (re)allocation, unless do_check is false, indicating to do reallocation regardless.
     **/
    void reallocate_c(bool do_check=true) {
        
        // unless the check should be ignored, do nothing if the 'init flag' indicates not yet setup ('\0').
        if(!do_check || *c) {
            // deallocate the space taken by the array
            delete[] c;
            // allocate space for a new array
            allocate_c();
        }
    }

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
        std::copy(dta.begin(), dta.end(), p);

        // if the array is to be null-terminated, set the final element to be a terminating null-character.
        if(nulled) {
            p[size()] = '\0';
        }

        // finally output the pointer to the array.
        return p;
    }
};

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