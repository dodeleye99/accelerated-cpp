#include <algorithm>
#include <string>

using std::equal;
using std::string;

// determines whether a string is a palindrome (spelled the same way front to back and back to front)
// E.g. "eye", "level", "rotor" are all palindromes
bool is_palindrome(const string& s)
{
    return equal(s.begin(), s.end(), s.rbegin());
}

/**
 * === ALGORITHMS ===
 * equal(s1, end, s2) - compares two sequences to determine whether they contain equal values.
 *      - first sequence are the elements [s1, end),
 *      - second sequence begins with s2, and is assumed to have the same size as the first.
 * ------------------
 * string::rbegin() - returns an iterator that starts with the last element in the container and traverses backwards through the containter
 **/