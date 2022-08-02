#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using std::cin;
using std::cout;
using std::back_inserter;
using std::copy;
using std::endl;
using std::istream;
using std::istream_iterator;
using std::ostream;
using std::ostream_iterator;
using std::vector;


// read integers from an input stream, storing them in a vector.
vector<int> read_int(istream& in)
{
    vector<int> v;
    
    /**
     * Read ints from the input stream and append them to v.
     * 
     * - istream_iterator<T>(s): represents an input iterator that reads objects of type T from input stream s.
     * - Thus the first constructor constructs an iterator associated with the input stream in.
     * - The second constructor (without any input arguments) produces an end-of-stream iterator.
     * 
     * This prepares the sequence of characters (text) to be read from the stream, to be appended to the end
     *  of the vector v, using (via back_inserter) an iterator pointing to its end 
     *  while allowing more to be added.
     **/
    copy(istream_iterator<int>(in), istream_iterator<int>(), back_inserter(v));

    return v;
}

// write integers from a vector to an output stream.
ostream& output_int(ostream& out, vector<int> v)
{
    /**
     * Write the ints of v to the output stream passed, each separated from the other by a space.
     * 
     * - ostream_iterator<T>(s, c): represents an output iterator that writes objects of type T to an output stream s.
     * after every write, a sequence of characters represented by the char pointer c is also written to the stream,
     *  acting as a delimiter (used to mark divisions between each written object).
     * 
     **/
    copy(v.begin(), v.end(), ostream_iterator<int>(out, " "));
    return out;
}

int main()
{   
    // prompt the user
    cout << "Input lines of integers, followed by end-of-file, to have them all written on a single line:" << endl;

    // read all integers inputted from the standard input stream, storing them in a vector.
    vector<int> v = read_int(cin);
    cout << endl;
    cout << "\nAll integers that were inputted:" << endl;
    // output all the integers from the vector, writting them on the standard output stream.
    output_int(cout, v);
    cout << endl;
    return 0;
}

/**
 * ==========
 * ALGORITHMS
 * ==========
 * copy(iter_1, iter_2, iter_out): writes a sequence of values pointed by the range of iterators [iter_1, iter_2) 
 * to another sequential collection or location, starting from the position pointed to by iter_out. 
 **/