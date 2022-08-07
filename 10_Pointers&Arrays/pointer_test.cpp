#include <iostream>
using std::cout;
using std::endl;


int main()
{
    int x = 5;

    // p points to x
    int* p = &x;
    cout << "x = " << x << endl;

    // change the value of x through p
    *p = 6;
    cout << "x = " << x << endl;
    return 0;
}

/**
 * ==========================
 * POINTERS IN C++:
 * ==========================
 * Declaring pointers:
 * 
 * typename * p_name
 * --------------------------
 * A pointer can be set to the adress of an object of corresponding type,
 * or to another pointer of the same type (including the initial pointer of an array - simply assign it to an array variable)
 * 
 * The address-of operator (&) is used to get the memory location of an object.
 * 
 * To access the value at the address the pointer 'points' to, use the dereferencing operator (*). 
 * It may also be used to modify. the valueat the address.
 **/