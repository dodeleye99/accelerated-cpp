#include <algorithm>
using std::copy;

#include <cstring>
using std::strlen;

/**
 * Returns the initial pointer of a new independent copy of an array of chacracters which has the initial character pointer p.
 **/
char* duplicate_chars(const char* p)
{
    // allocate enough space; remember to add one for the null
    size_t length = strlen(p) + 1;
    char* result = new char[length];

    // copy into our newly allocated space and return pointer to the first element
    copy(p, p + length, result);
    return result;
}

/**
 * strlen() returns the length of a character array with a null character at the end (i.e. a string literal).
 * (This length does NOT count the null character)
 **/

/**
 * =====================================================
 * DYNAMIC MEMORY ALLOCATION - AN OVERVIEW
 * =====================================================
 * -----------------------------------------------------
 * WHAT IS IT AND WHY IS IT USEFUL?
 * -----------------------------------------------------
 * If a variable will always use the same size of memory, the amount of memory it needs can easily be predetermined before program execution,
 * and the exact memory needed is reserved for it at compile time in the memory stack.
 * 
 * However, this is not always the case, as there may be cases where the memory needs of a variable can only be determined at runtime. 
 * For example, in reading a string from the standard input stream, the memory needed will depend on user input.
 * 
 * In such cases of uncertainty a program needs to dynamically allocate memory (that is, distribute and reserve space), 
 * which is possible in C++ with the 'new' operator.
 * 
 * We can allocate memory for either a single object, or an array of objects, using the operator 'new' in the following way:
 * type * p = new type;
 * type * p = new type[n]
 * 
 * This is in constast to normal, automatic allocation:
 * type * p;
 * type a[const_n];
 * 
 * There is a major difference between normal arrays and dynamically allocated arrays.
 *  - The size of a normal array NEEDS to be a CONSTANT expression, since the compiler needs to know how much space to reserve for it before the program is run.
 *  - In contrast, dynamically allocated arrays allow one to assign memory during runtime using a (non-constant) variable as its size. 
 *    This allocated memory is taken from the memory heap.
 * -----------------------------------------------------
 * WHAT ABOUT MEMORY DEALLOCATON?
 * -----------------------------------------------------
 * After the varaible is no longer needed, one can deallocate its memory by using the operator 'delete':
 * delete p;
 * delete[] p;
 * 
 * It destoys the assigned object and frees the memory, making it freely available for other requests of the dynamic memory.
 * -----------------------------------------------------
 * WHAT IF THERE IS NOT ENOUGH SPACE TO ALLOCATE MEMORY?
 * -----------------------------------------------------
 * It may be possible for the program to fail to allocate memory for a request, in the case of insufficient space available. 
 * In such cases an exception is thrown (bad_alloc), except if '(nothrow)' is used when allocating memory, following the 'new' keyword.
 * In the latter case a null pointer (nullptr) is returned, which is a pointer with no particular address (zero).
 * The program should therefore take measures to catch and handle such errors or potential null pointers. 
 **/