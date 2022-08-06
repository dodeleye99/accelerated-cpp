# Chapter 10: Pointers and Arrays

This chapter focuses on two concepts built into C++ that originated from the C programming language: pointers and arrays.

* A **pointer** is a **random-access iterator** that holds the **address** (memory location) of an object. They are able to "point" to single objects, arrays of objects, and even functions. To define a pointer variable in C++, one has to specify the object type it will point to _followed_ by an asterix/star `*` character _before_ the variable name when first declaring it. This can the nested by adding another `*`, in that one can define a pointer that points to another pointer of a certain type.

* An **array** is a fixed-size, built-in **container** whose iterators are pointers (random-access). To declare an array variable, one has to specify the object type each of its values will be before writting variable name, after which one must specify the size of the array within closed brackes `[]`. They may also be initialised immediately (without needing to specify its size, leaving the closed brackets empty) by assigning it to a sequence of comma-separated values closed by curly brackets `{...}`.

    In previous chapters arrays have actually been heavily used, though implicitly. In particular, a **string literal** is in reality a mnemonic for an array of characters, with a null pointer element `'\0'` at the end to indicate the end of the array. It can nevertheless be thought of as a "string".

In C++, arrays can be made to behave as pointers; anytime the name of an array is used as a value, it is automatically converted to a pointer to the initial element of the array. The other elements can be obtained using any of the pointer operators for accessing values of a container:

* the addition operator `+` to advance the initial pointer by a given number of places. The value can then be obtained by applying the dereference `*` operator to the result.
    * the incrementation operator `++` to advance the initial pointer only by one place.
* more approprately, the indexing operator `[]` to get the value of the array at a given position relative to the initial position.

It is not possible, however, to assign an entire array to another value, even another array. On the left-side of the assignment `=` operator, it will not behave as a pointer, but as an array to be modified using the `[]` operator as shown above, unless it was declared using the `const` keyword, in which none of its elements can be changed again.

### Directories of Code:
1) `main_args.cpp`

### Extensions:

### New Concepts:
* Defining pointers and arrays in C++, as shown above.
* Defining a 'nested' pointer: a pointer that 'points' to a pointer.
* The address-of operator `&`, used to obtain the address of an existing object that can then be assigned to a pointer.
* Dynamic memory allocation and deallocation using the `new` and `delete` operators respectively.
