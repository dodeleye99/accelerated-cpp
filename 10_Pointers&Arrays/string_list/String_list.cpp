// implementation of the 'copy' constructor, and the resize() and push_back() member functions of String_list
#include <algorithm>
using std::copy;

#include <string>
using std::string;

#include "String_list.h"


String_list::String_list(const String_list& sl)
{   
    // Create a new array (with same size as the source-list) for storing this copy list.
    l = new string[sl.size()];
    sz = sl.size();
    
    // Copy contents of the source list to this copy list.
    copy(sl.begin(), sl.end(), l);

}

void String_list::resize()
{
    // We "resize" the fixed array by replacing it with one that has DOUBLE the original size
    max_size *= 2;

    // Create a new array with the increased size, allocating the necessary space.
    string *s = new string[max_size];


    // Copy the list elements in the original array to the fromt of the new array.
    size_type i = 0;
    for(size_type i = 0; i != sz; ++i)
        s[i] = l[i];

    // Remember to deallocate the memory of the orignal array, freeing it for possible use elsewhere
    delete[] l;

    // Assign the list (pointer) member to this new array (pointer to its first element).
    l = s;
}
void String_list::push_back(string s)
{
    // If there is no more space in fixed array the list is stored in, we must first "resize" it.
    if(sz == max_size) {
        resize();
    } 
    // Add the string to the end of the list.
    l[sz] = s;
    // Increment the size of the list.
    ++sz;
}
