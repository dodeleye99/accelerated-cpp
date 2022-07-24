#include <iostream>
#include <string>

// This makes the program assume the scope to be the std namespace 
using std::cout;    using std::endl;
using std::string;

int main()
{
    // number of rows the triangle will take
    const int height = 10;

    // invariant: 'r' rows of the triangle have been drawn.
    for(int r = 0; r != height; ++r) {

        // are we currently drawing the top or bottom of the triangle?
        if(r == 0 || r == height - 1) {
            string triangle_end(r+1, '*');
            cout << triangle_end;
        } else {
            int spaces = r - 1;
            string triangle_inner(spaces, ' ');
            cout << "*" + triangle_inner + "*";
        }
        // end the row
        cout << endl;
    }

    return 0;
}