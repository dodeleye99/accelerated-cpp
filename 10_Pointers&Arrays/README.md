# Chapter 10: Pointers and Arrays

This chapter focuses on two concepts built into C++ that originated from the C programming language: pointers and arrays.

* A **pointer** is a **random-access iterator** that holds the **address** (memory location) of an object. They are able to "point" to single objects, arrays of objects, and even functions. To define a pointer variable in C++, one has to specify the object type __followed__ by an asterix/star `*` character when first declaring it.

* An **array** is a fixed-size, built-in **container** whose iterators are pointers. In previous chapters arrays have actually been heavily used, though implicitly. In particular, a **string literal** is in reality a mnemonic for an array of characters, with a null pointer element `'\0'` at the end to indicate the end of the array.

In C++, arrays can be made to behave as pointers; anytime the name of an array is used as a value, it is automatically converted to a pointer to the initial element of the array.

### Directories of Code:
1) `main_args.cpp`

### Extensions:

### New Concepts:
* Defining pointers in C++
* The address-of operator `&`, used to obtain the address of an existing object that can then be assigned to a pointer.
