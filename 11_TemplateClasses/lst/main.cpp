#include <iostream>
using std::cout;
using std::endl;

#include "Lst.h"
#include "nrand.h"

#include <string>
using std::string;

// Outputs a sequence of values from a range of iterators [first, last)
template <class InputIterator> 
void output_values(InputIterator first, InputIterator last){

    for(InputIterator iter = first; iter != last; ++iter) {
        cout << *iter << " ";
    }
    cout << endl;

}

template <class T, class InputIterator, class ForwardIterator> 
void insert_sort(InputIterator first, InputIterator last, ForwardIterator dest) {
    for(InputIterator iter=first; iter != last; ++iter) {
        

    }
}

int main(int argc, char** argv)
{   
    // Type definitions
    typedef Lst<int> IntLst;
    typedef Lst<string> StrLst;
    typedef Lst<bool> BoolLst;

    typedef IntLst::iterator int_iter;
    typedef IntLst::const_iterator cint_iter;
    typedef IntLst::reverse_iterator int_rev_iter;
    typedef IntLst::const_reverse_iterator cint_rev_iter;

    typedef StrLst::iterator str_iter;
    typedef StrLst::const_iterator cstr_iter;
    typedef StrLst::reverse_iterator str_rev_iter;
    typedef StrLst::const_reverse_iterator cstr_rev_iter;

    typedef BoolLst::iterator bool_iter;
    typedef BoolLst::const_iterator cbool_iter;
    typedef BoolLst::reverse_iterator bool_rev_iter;
    typedef BoolLst::const_reverse_iterator cbool_rev_iter;

    // =========== TEST 1: Lst of strings ===========

    // Create a lst holding each of the command line argumants
    StrLst str_lst(argv, argv + argc);

    // Output them in reverse order
    output_values(str_lst.rbegin(), str_lst.rend());

    // Insert "*pant*" between each element
    for(str_iter iter = str_lst.begin(); iter != str_lst.end(); ++iter) {
        str_lst.insert(iter, "*pant*");
    }
    // Output the modfiied lst in the ususal order
    output_values(str_lst.begin(), str_lst.end());

    // =========== TEST 2: Lsts of ints and bools ===========

    // Create an empty lst for integers
    IntLst int_lst1;

    // Add 20 random numbers from the range [1,100]
    for(size_t i=0; i != 20; ++i) {
        int_lst1.push_back(nrand(100));
    }
    
    /**
     * Create a second lst of bools, same size as the first, 
     * but consisting of only default valued (false) bools
     **/
    BoolLst bool_lst(int_lst1.size());
 
    // Use this bool lst to mark which ints are even.
    cint_iter int_riter  = int_lst1.begin();
    bool_iter bool_witer = bool_lst.begin();
    while(int_riter != int_lst1.end())
    {   
        // get the value at the current position
        int v = *int_riter++;
        // if the value is even, mark true at the corresponding position in the bool lst.
        if(v % 2 == 0) {
            *bool_witer = true;
        }
        bool_witer++;
    }

    // Create a copy of the first int lst, to be used to hold all the evens
    IntLst int_evens(int_lst1);
    // Create an empty int lst, to be used to hold all the odds
    IntLst int_odds;

    // Extract all the odds from the evens lsts
    int_iter   evens_iter = int_evens.begin();
    cbool_iter bool_riter = bool_lst.begin();

    while(bool_riter != bool_lst.end())
    {   
        // if position marks even, pass it.
        if(*bool_riter++) {
            ++evens_iter;
        }
        // otherwise, extract it from the even lst, adding it to the odd lst
        else {
            int_odds.push_back(*evens_iter);
            evens_iter = int_evens.erase(evens_iter);
        }
    }

    // Output the integer lsts
    cout << "\nOutputting 20 random integers from range [0, 100]: " << endl;
    output_values(int_lst1.begin(), int_lst1.end());

    cout << "\nOdd numbers:  ";
    output_values(int_odds.begin(), int_odds.end());

    cout << "Even numbers: ";
    output_values(int_evens.begin(), int_evens.end());


    // =========== TEST 3: Sorting a Lst of ints ===========

    // Reuse int_odds for the lst of sorted values, using a reference to it with more approprate name
    IntLst& int_lst2 = int_odds;
    // First clear the lst
    int_lst2.clear();

    // Now do an insertion sort, inserting each element from int_lst1 into int_lst2 in ascending order
    for(cint_iter iter1 = int_lst1.begin(); iter1 != int_lst1.end(); ++iter1) {
        
        // iteratre through the lst to find the right position to insert the value
        int_iter iter2 = int_lst2.begin();
        while(iter2 != int_lst2.end() && *iter1 > *iter2) {
            ++iter2;
        }
        // insert the value
        int_lst2.insert(iter2, *iter1);
    }

    // Finally output the sorted lst
    cout << "\nSorted values: " << endl;
    output_values(int_lst2.begin(), int_lst2.end());

}