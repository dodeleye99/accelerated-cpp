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

    // === PART 0: SETTING UP VEC ===

    // add integers in range [0, 21) to the Vec
    for (int i=0; i != 21; ++i){
        v.push_back(i);
    }

    cout << "======= The initial Vec =======" << endl;
    // output the elements of the Vec
    for(c_iter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // === PART 1: CONSIDERING A PARTICULAR ITERATOR ===

    // get an iterator to the 10th element (9).
    iter iter1 = v.begin() + 9;

    // output the state of the iterator
    cout << "\nIterator to 10th element:" << endl;
    cout << "Address: " << iter1 << "\nValue: " << *iter1 << endl;

    // === PART 2: ERASING AN ELEMENT AT A POSITION AFTER THE ITERATOR ===

    // erase the last element
    v.erase(v.end() - 1);
    cout << "\n======= After erasing last element =======\n" << endl;

    // output the elements of the Vec
    for(c_iter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // output the state of the iterator
    cout << "\nIterator to 10th element:" << endl;
    cout << "Address: " << iter1 << "\nValue: " << *iter1 << endl;


    // === PART 3: ERASING AN ELEMENT AT A POSITION BEFORE THE ITERATOR ===

    // erase the first element
    v.erase(v.begin());
    cout << "\n======= After erasing first element =======\n" << endl;

    // output the elements of the Vec
    for(c_iter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // output the (new?) state of the iterator
    cout << "\nIterator to 10th element:" << endl;
    cout << "Address: " << iter1 << "\nValue: " << *iter1 << endl;

    cout << "\nDid something change?" << endl;

    // === PART 4: CLEARING THE ENTIRE VEC ===
    
    // empty the Vec
    v.clear();
    cout << "\n======= After clearing the whole Vec =======\n" << endl;

    // output the (new?) state of the iterator
    cout << "Iterator to 10th element:" << endl;
    cout << "Address: " << iter1 << "\nValue: " << *iter1 << endl;
    cout << "\nDid the value change as a result of the clear?" << endl;

    // === PART 5: REFILLING THE ENTIRE VEC ===

    // add integers in range [-20, 1) to the Vec
    for (int i=-20; i != 1; ++i){
        v.push_back(i);
    }

    cout << "\n======= After adding values from -20 to 0 to the Vec =======\n" << endl;

    // output the elements of the Vec
    for(c_iter it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // output the (new?) state of the iterator
    cout << "\nIterator to 10th element:" << endl;
    cout << "Address: " << iter1 << "\nValue: " << *iter1 << endl;
    cout << "\nDid the value change?\n" << endl;

}