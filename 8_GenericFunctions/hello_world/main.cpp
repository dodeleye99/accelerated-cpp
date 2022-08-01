#include <iostream>

#include "zero.h"

using std::cout;
using std::endl;


int main()
{
    cout << "Hello, world!" << endl;

    /**
     * Since the type-parameter does not appear at all in the argument list,
     * we must explicitly qualify zero with the actual type that cannot be infered using '<>' brackts.
     */
    return zero<int>(); // Calls zero() with type parameter "int".
}