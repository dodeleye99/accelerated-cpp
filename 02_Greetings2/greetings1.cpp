#include <iostream>
#include <string>

int main()
{
    std::cout << "Please enter your first name: ";

    // read the name
    std::string name;
    std::cin >> name;

    // build the message that we intend to write
    const std::string greeting = "Hello, " + name + "!";

    // we have to rewrite this part...

    // the number of blanks surrounding the greeting
    const int pad = 5;

    // total number of rows and columns write
    const int rows = pad * 2 + 3;
    const std::string::size_type cols = greeting.size() + pad * 2 + 2;

    // separate the output from the input
    std::cout << std::endl;

    // write 'rows' rows of output
    int r = 0; 
    // setting r to 0 makes the invariant true

    // (invariant: we have written r rows so far)
    while(r != rows){

        // we can assume that the invariant is true here

        std::string::size_type c = 0;

        // (invariant: we have written c characters so far in the current row)
        while (c != cols){

            // are we on the border?
            if(r == 0 || r == rows - 1 || c == 0 || c == cols - 1){
                std::cout << "*";
                ++c;
            } else{
                // (write one or more characters)
                // (adjust the value of c to mantain the invariant)

                // is it time to write the greeting?
                if(r == pad + 1 && c == pad + 1){
                    std::cout << greeting;
                    c += greeting.size();
                } else{
                    std::cout << " ";
                    ++c;
                }
            }
           
        }

        // writing a row of output makes the invariant false
        std::cout << std::endl;
        // incrementing r makes the invariant true again
        ++r;
    }
    // we can conclude that the invariant is true here

    return 0;
}
/*
The operator ++ is used to increment a value.
    ++x increments x and THEN outputs its (new) value
    x++ outputs the (initial) value of x BEFORE incrementing it.
*/
