# Chapter 10: Pointers and Arrays

This chapter extensively focuses on two concepts built into C++ that originated from the C programming language: pointers and arrays.

* A **pointer** is a **random-access iterator** that holds the **address** (memory location) of an object. They are able to "point" to single objects, arrays of objects, and even functions. To define a pointer variable in C++, one has to specify the object type it will point to _followed_ by an asterix/star `*` character _before_ the variable name when first declaring it. This can the nested by adding another `*`, in that one can define a pointer that points to another pointer of a certain type.

* An **array** is a fixed-size, built-in **container** whose iterators are pointers (random-access). To declare an array variable, one has to specify the object type each of its values will be before writting variable name, after which one must specify the size (a constant) of the array within closed brackes `[]`. They may also be initialised immediately (without needing to specify its size, leaving the closed brackets empty) by assigning it to a sequence of comma-separated values closed by curly brackets `{...}`.

    In previous chapters arrays have actually been heavily used, though implicitly. In particular, a **string literal** is in reality a mnemonic for an array of characters, with a null pointer element `'\0'` at the end to indicate the end of the array. It can nevertheless be thought of as a "string".

In C++, arrays can be made to behave as pointers; anytime the name of an array is used as a value, it is automatically converted to a pointer to the initial element of the array. The other elements can be obtained using any of the pointer operators for accessing values of a container:

* the addition operator `+` to advance the initial pointer by a given number of places. The value can then be obtained by applying the dereference `*` operator to the result.
    * the incrementation operator `++` to advance the initial pointer only by one place.
* more approprately, the indexing operator `[]` to get the value of the array at a given position relative to the initial position.

It is not possible, however, to assign an entire array to another value, even another array. On the left-side of the assignment `=` operator, it will not behave as a pointer, but as an array to be modified using the `[]` operator as shown above, unless it was declared using the `const` keyword, in which none of its elements can be changed again.

### Directories of Code:
1) [`main_args`](main_args) introduces a second form of the `main()` function, which takes two parameters that represent text inputted into command line immediately following the execution call. The program demonstrates its use, by outputting the text the user entered.

2) [`file_copier`](file_copier) introduces the concept of file reading and writting. It takes as a command-line argument a file as input and copies its contents to another file. The user can also choose themselves which files to copy the input file to, by adding them as aditional command-line arguments.

3) [`file_reader`](file_reader) receives one or more files as command-line arguments and outputs the contents of each one that exists.
### Extensions:
4) [`records1`](records1) returns to the student grading system. It now assigns letter grades for each student based on their final grades (for example, a final grade in the inclusive range 80-83 is a `"B-"`), outputting it along with the numerical grade. It does this by creating two static arrays holding the numerical grade lower bounds and the letter grades respectively, with elements from each array that have matching indices corresponding to each other.

5) [`records2`](records2) improves upon `records1` by now allowing the user to enter one or more input files containing student data as a command line argument, as well as an output file to write the results to. If no input files are specified, then the user must enter them the usual way. If input files were entered but none could be opened, the program will end with an approprate message. If no output directory is specified, a default one will be used.

6) [`records3`](records3) improves upon `records2` by allowing the user to choose (not as a command-line argument but within the program) between outputting the grades the usual way, or outputting all the passing students followed by all the failing students (whose letter grades do not need to be mentioned, as they will all be `"F"`). 

    It uses code that presents a formal, organised way of representing each of the user's possible choices, by defining a small class called [`Option`](records3/Option.h) (defined using the `struct` keyword to allow public access). It holds two members, one representing text to briefly describe the option to the user, and the other representing the actual processing function for writting the grades. 
    
    It also introduces the concept of function pointers as well as null pointers.
    
### References:
7) [`pointer_test.cpp`](pointer_test.cpp) demonstrates how pointers work by modifying the value of the variable through a pointer alone.

8) [`duplicate_chars.cpp`](duplicate_chars.cpp) defines a function that takes a character pointer representing an array and outputs a pointer to an new, independent copy of the array. It introduces the concept of dynamic memory allocation (see comments at the bottom of the file), which is used to carry it out.

9) [`string_list`](string_list) demonstrates how one may implement a list of strings using arrays and pointers, by defining a class called [`String_list`](string_list/String_list.h). The code found in the directory returns to the sentence splitting program established in earier chapters to show how this class can be used in place of a `vector<string>`.

### New Concepts:
* Defining pointers and arrays in C++, as shown above.
* Defining a 'nested' pointer: a pointer that 'points' to a pointer.
* The address-of operator `&`, used to obtain the address of an existing object that can then be assigned to a pointer.
* Dynamic memory allocation and deallocation using the `new` and `delete` operators respectively, allowing us to define arrays or pointers with a size only known during runtime.
* The two-parameter form of the `main()` function, which uses command-line arguments the user can pass to it when executing the program.
* Reading from and writting to files using `ifstream` and `ofstream` objects respectively.
* Using the `ifstream::seekg()` member function to enable a file to be re-read from the beginning.
* Contant valued arrays, which have elements that are read-only (cannot be modified).
* Constant pointers, which cannot be made to point to another address.
* Calculating the capacity of an array by doing basic division with the `sizeof()` function (more precisely, `sizeof(array) / sizeof(*array)`).
* The `typename` keyword, used to indicate that a name in a given scope is a type (important for template type parameters).
* Null pointers, which do not point to any address at all, and can be defined and identified through the `nullptr` keyword.
* Pointers to functions, and defining a type mnemonic for a pointer to functions of a given type (return and parameter list).
