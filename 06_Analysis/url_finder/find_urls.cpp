#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using std::isalpha;
using std::isalnum;
using std::find;
using std::find_if;
using std::string;
using std::vector;


// determines whether a character is one that may appear in a URL
bool not_url_char(char c)
{   
    // characters, in adition to alphanumerics, that can appear in a URL
    static const string url_ch = "~;/?:@=&$-_.+!*'(),";

    // see whether c can appear in a URL (and return the negative
    return !( isalnum(c) || find(url_ch.begin(), url_ch.end(), c) != url_ch.end() );

    // find(begin, end, c) is the same as:
    //// iter i = begin
    //// while(i != end &&  *i != c)
    ////    ++i;
    //// return i;
}

// finds the beginning of any URL in the input (all valid characters before the first :// found) (?)
string::const_iterator url_beg(string::const_iterator b, string::const_iterator e)
{
    // the separator between the beginning of the url and the main part.
    static const string sep = "://";
    
    typedef string::const_iterator iter;

    // i marks where the separator was found
    iter i = b;

    /**
     * Search the part of the input string bound by the range of iterators [i, e]
     *  for the start iterator poining to the first occurance of a separator.
     * Then assign this value to i. If not found, then end loop.
     **/
    while ( ( i = search(i, e, sep.begin(), sep.end()) ) != e) {

        // make sure the separator isn't at the beginning or end of the line
        if (i != b && i + sep.size() != e) {

            // find the part of the string before the separator that
            // beg marks the beginning of the protocol-name
            iter beg = i;
            while (beg != b && isalpha(beg[-1]))
                --beg;

            // is there at least one appropriate character before and after the separator?
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;

        }
        // the separator we found wasn't part of a URL; advance i past this separator
        i += sep.size();
    }
    return e;
}

// finds the end of any URL in the input (all valid characters starting from b)
string::const_iterator url_end(string::const_iterator b, string::const_iterator e)
{
    return find_if(b, e, not_url_char);
}

vector<string> find_urls(const string& s)
{
    vector<string> ret;
    typedef string::const_iterator iter;
    iter b = s.begin(), e = s.end();
    
    // look through the entire input
    while (b != e) {

        // look for one or more letters followed by ://
        b = url_beg(b, e);

        // if we found it
        if (b != e) {
            // get the rest of the URL
            iter after = url_end(b, e);

            // remember the URL
            ret.push_back(string(b, after));

            // advance b to check for more URLs on this line
            b = after;
        }
    }
    return ret;
}


/**
 * === ALGORITHMS ===
 * isalnum(c) - determines whether a character is alphanumeric. That is, any letter (a-z or A-Z) or any digit (0-9).
 * ------------------
 * isalpha(c) - determines whether a character is an alphabetical letter (a-z or A-Z)
 * ------------------
 * search(first1, last1, first2, last2) - searches a container within the range of iterators [first1, last1) 
 *  for the first occurence of a sequence of values specified by the range of iterators [first2, last2),
 *  returning the iterator to the first element. If none found, then last1 is returned.
 **/