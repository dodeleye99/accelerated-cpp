# Chapter 8: Generic Functions

This chapter explores special kinds of functions, known as generic functions. These are functions with one or more arguments with types only restricted by the operations performed on them in the function.

C++ implements generic functions through the defining of what are known as templete functions. This simply involves writting a single definition for a family of functions (or types) that behave similarly. 

Generic functions are naturally based around the concept of polymorphism, the ability of a function to adapt and suport multiple types of its arguments.

Because of their special nature, the compiler automatically generates out of templates separate functions each with parameter types that match the calls to the template found in the source code. For this reason template functions must be defined in the same file that it was declared. Therefore, we usually must not only declare, but also implement templates in a header file rather than a C++ source file.

### Directories of Code:


### Extension:

### New Concepts:
* Defining generic functions, as explained above.
