#ifndef GUARD_String_list_h
#define GUARD_String_list_h

#include <cstddef>
#include <string>

// Class used to represent a list of strings
class String_list {

// ---- Private (class-access only) members ---- 
private:

    // Represents a pointer towards the first element of a array of strings.
    std::string *l;
    // Represents the current size of the list
    std::size_t sz;
    /**
     * Represents the size of the current (fixed-size) array represnting the list.
     * (The array may need to be replaced with a larger array to allow for more elements to be added)
     **/
    std::size_t max_size;

    // A function used to "resize" the array (i.e. reallocate memory) to allow for more elements.
    void resize();

// ---- Public (free access) members ---- 
public:

    // A mnemonic for a pointer to an element of the list.
    typedef std::string* iterator;
    // A mnemonic for the type representing the size of the list.
    typedef std::size_t size_type;

    // The (default) constructor for initialising the string list (initially empty, with array size 1).
    String_list(): l(new std::string[0]), sz(0), max_size(1) { }

    // Constructor for initialising a copy of an already established string list.
    String_list(const String_list&);

    // A function used to add a string to the end of the list.
    void push_back(std::string);

    // Returns a pointer to the first element of the list.
    iterator begin() const { return l;}

    // Returns a pointer to the end (one-past the last element) of the list.
    iterator end() const { return l + sz;}

    // Returns the size (number of added elements) of the list (NOT the entire array).
    size_type size() const { return sz;}

    // A predicate for whether the list is empty (no elements).
    bool empty() const { return begin() == end();}

};

#endif