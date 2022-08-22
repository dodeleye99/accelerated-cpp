#include <algorithm>    // std::copy
#include <cstring>      // std::strlen
#include <iostream>     // std::istream, std::ostream
#include <iterator>     // std::back_inserter

#include "Vec.h"

/**
 * A simplified version of the std::string class. used to implement strings.
 * In reality, it is simply a "wrapper class" of  Vec<char>,
 * which is a particular instance of the Vec template class.
 **/
class Str {
    /**
     * Use the 'friend' keyword to give the operator>>() function (only the one that takes istream and Str) 
     * access rights to private members of a Str object (particularly the 'data' member variable). 
     * 
     * This is more optimal than making members public, since it enables us to still hide the implementation
     * details from the user, while also preventing them from accessing and modifying them.
     */
    friend std::istream& operator>>(std::istream&, Str&);
public:
    
    // type used to represent size of the Str
    typedef Vec<char>::size_type size_type;

    // --------------- Constructors ---------------
    
    /**
     * Default constructor; create an empty Str
     * (must be explicitly defined since the class has other constructors, even if left blank,
     * otherwise the user will be unable to declare a Str)
     **/
    Str() { }

    // create a Str containing n copies of c
    Str(size_type n, char c): data(n, c) { }

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
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }

    // create a Str from the range denoted by iterators b and e
    template <class In> Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }

    /** 
     * Note that we did not define the copy constructor, assigment operator and destructor.
     * This is because the complier will automatically synthesise these, each of which does 
     * exactly what we require - carring out the same operations on the underlying data Vec, 
     * which does all memory allocation and deallocation for us already.
     **/

    // --------------- Operators ---------------

    // indexing operator, returning a reference to the char at a given position, allowing it to be modified.
    char& operator[](size_type i) { return data[i]; }
    // (for read-only)
    const char& operator[](size_type i) const { return data[i]; }

    // concatenation operator, joining the characters of a given Str to the end of this Str.
    Str& operator+=(const Str& s) {
        // copy the characters of the right operand to those of the left operand (this Str)
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        // return a refrence to the left operand (this Str), giving the final result.
        return *this;
    }

    // --------------- Other member functions ---------------

    // outputs the number of chars that make up the Str
    size_type size() const { return data.size(); }
private:
    /**
     * represents the underlying data structure used to implement 
     * the Str: a Vec of chars.
     **/
    Vec<char> data;
};

// ------------------- Non-member operators -------------------

// reads input from an input stream, storing what was read in a given Str
std::istream& operator>>(std::istream&, Str&);

// writes the value of a given Str to an onput stream
std::ostream& operator<<(std::ostream&, const Str&);

/** 
 * Concatenates two Strs, producing a new Str made up of the characters of each individual Str, joined end to end.
 * 
 * It is important that we define this as a non-member function. Otherwise, the operator would be asymmetric,
 * with odd behaviour when type conversions (const char* to Str) are in view
 * 
 * For example, suppose x is a Str, while y is a char*.
 * Then
 *                  z = x + y   // x.operator+(y)
 * 
 * works by first converting y to a temporary Str through the constructor Str(const char*), and concatenates
 * it with x, storing the result in z.
 * 
 * However, if operator+ was a member of Str, and knowing that char* channot directly concatenate with Strs, then
 * 
 *                  z = y + x   // attempts y.operator+(x), but char*, which is not a class type, has no such function.
 * 
 * would fail to comiple, since in such cases (member operators) the compiler does NOT convert the left operand, 
 * except if operator+ is a non-member (taking y and x, the first being converted to a Str).
 * 
 **/
Str operator+(const Str&, const Str&);
