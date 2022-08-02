# Chapter 8: Generic Functions

This chapter explores special kinds of functions, known as generic functions. These are functions with one or more arguments with types only restricted by the operations performed on them in the function.

C++ implements generic functions through the defining of what are known as function templates. This simply involves writting a single definition for a family of functions (or types) that behave similarly. 

Generic functions are naturally based around the concept of polymorphism, the ability of a function to adapt and supprt multiple types of its arguments (and even its return type).

Because of their special nature, the compiler automatically generates out of templates separate functions each with parameter types that match the calls to the template found in the source code. For this reason template functions must be defined in the same file that it was declared. Therefore, we usually must not only declare, but also implement templates in a header file rather than a C++ source file.

### Directories of Code:
1) **hello_world** represents a basic "Hello World" program, but implemented in an interesting way to demonstrate the use of function template.
The twist is that the integer-typed zero returned by the main() function is replaced by a function that outputs zero with a type that matches a given type-parameter, which in this case must be int.
2) **sentence_split** returns to the splitting functions defined and used in previous chapters, this time implementing it using a template that allows the function to be applied to any output iterator.
3) **int_reader** explores how iterators on input and output streams can be used to read input and write output respectively only of a single type, in this case integers.

### Extension:

### New Concepts:
* Defining generic functions using templates, as explained above.
* Specifying the type parameter of a function template call, necessary when it cannot be inferred implicitly.
* Defining namespaces to group related names together in a new scope.
* Input (read) iterators, that can access/read (but may not be able to reassign) the values that they point to.
* Output (write) iterators, that can reassign (but may not be able to read) the values that they point to.
* Input and output stream iterators, used to sequentially read from an input stream and to write to an output stream respectively.
