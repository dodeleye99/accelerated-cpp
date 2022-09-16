// program that builds and displays an interface design for a Tetris program
#include <iostream>
#include <string>
#include <vector>

#include "char_pic.h"
#include "tetris_interface.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;


int main()
{
    const vector<string> interface = build_interface();

    for (vector<string>::const_iterator iter = interface.begin(); iter != interface.end(); ++iter)
    {
        cout << *iter << endl;
    }
    return 0;
}