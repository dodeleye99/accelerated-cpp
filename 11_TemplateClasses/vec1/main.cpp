#include <iostream>
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include "Vec.h"


int main()
{
    // assume our Vec will hold int types.
    typedef Vec<int> Vector;

    typedef Vector::iterator iter;
    typedef Vector::const_iterator c_iter;
    
    // create a new Vector
    Vector v;

    // add initial element to the Vector
    v.push_back(0);

    // get an iterator to this element.
    iter first1 = v.begin();

    // add many elements to Vector
    for (int i=1; i != 20; ++i){
        v.push_back(i);
    }

    // output the elements of the Vec
    for(c_iter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // get another(?) iterator to the "initial element".
    iter first2 = v.begin();

    // modify the "initial element"
    *first2 = -1;
    cout << "\n(After changing first element from 0 to -1)\n" << endl;

     // One may expect these to be the same
    cout << "First Iterator to Initial Element:" << endl;
    cout << "Address: " << first1 << "\nValue: " << *first1 << endl;

    cout << "\nSecond Iterator to Initial Element:" << endl;
    cout << "Address: " << first2 << "\nValue: " << *first2 << endl;

    cout << "\nAre they the same?\n" << endl;
}