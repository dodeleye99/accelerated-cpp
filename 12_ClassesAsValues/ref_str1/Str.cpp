#include <algorithm>
using std::copy;

#include <cctype>
using std::isspace;

#include <cstring>
using std::strcmp;

#include <iostream> 
using std::istream;
using std::ostream;

#include <iterator>
using std::ostream_iterator;

#include "Str.h"


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
    s.dta.clear();

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
        do s.dta.push_back(c);
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
    s.dta.clear();

    // declare a new char used to store characters read by the stream
    char c;

    /**
     * Until an end-of-file (or istream error) is reached, or a delimiter is found, read and add each 
     * non-delimiter character to the end of the Str. The delimiter found is extracted from the stream 
     * and discarded.
     **/
    while(is.get(c) && c != delim) {
        s.dta.push_back(c);
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