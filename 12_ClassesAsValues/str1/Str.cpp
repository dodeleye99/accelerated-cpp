#include <cctype>
using std::isspace;

#include <iostream> 
using std::istream;
using std::ostream;

#include "Str.h"


ostream& operator<<(ostream& os, const Str& s) 
{
    // simply write each character representing the Str to the output stream one by one.
    for (Str::size_type i = 0; i != s.size(); ++i) {
        os << s[i];
    }
    /**
     * Remember to return the output stream, to allow for repeated writes
     * (i.e. os << s1 << s2 ... << sn)
     **/
    return os;
}

istream& operator>>(istream& is, Str& s) 
{
    // obliterate existing value(s), to ensure it is entirely replaced with the text read by the stream
    s.data.clear();

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
        do s.data.push_back(c);
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
    // construct a copy of one of the two operands
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