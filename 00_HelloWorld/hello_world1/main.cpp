// a small C++ program

// We need the standard header that is used for input-output.
#include <iostream>

int main()
{
    // With the << operator, use the stream denoted by cout (which comes from the std (standard) namespace) to output the next.
    // Then, from the same stream, use the manipulator, denoted by endl, to mark the end of the line.

    std::cout << "Hello, world!" << std::endl;

    std::cout << "This \" is a quoute, and this \\ is a backslash." << std::endl;

    std::cout << "This large space (\t) is from a tab character" << std::endl;
    return 0;
}
/* 
- '<<' is the standard library's output operator.
- '::' is the scope operator, used to get the specific name from the left defined in the scope on the right.
- 'std' refers to the namespace consisting of all names defined by the standard library.

- 'std::cout << e': writes the value of e on the standard-output stream, and yields std::cout, which has
type ostream, as its value in order to allow chained output operations.

To RUN this progam, first compile by running 
    gcc -o runme hello_wold.cpp
in the terminal. Then we can run
    ./ runme
*/

