# Accelerated C++

Code derived from the [**Accelerated C++**](https://www.informit.com/store/accelerated-c-plus-plus-practical-programming-by-example-9780201703535) textbook by Andrew Koenig and Barbara E. Moo. 

Note that it only uses concepts found no later than C++98.

## [Intro: Hello World!](00_HelloWorld)
This serves as an introductory chapter, showcasing the basic **"Hello, World!"** program and consequently a few of the basic concepts of C++.

This includes the `main()` function, standard output, string literals, standard headers, and escape sequences.

## [Chapter 1: Greetings - Part 1](01_Greetings1)
This chapter introduces standard input in C++, showcasing programs that ask for the user's name and return with an approriate greeting.

It also introduces the `string` type from the C++ standard library, used to represent a sequence of characters in a convenient way. 

## [Chapter 2: Greetings - Part 2](02_Greetings2)
This chapter extends from [Chapter 1](01_Greetings1), while introducing a vast number of basic concepts.

This includes defining integers through the `int` type, defining variables that cannot be reassigned after declaration (know as constants) through the `const` keyword, iteration through `while` loops and `for` loops, conditional statements (`if-else`), and arithmetic and logical operators.

It also demonstrates how one can define their own function,and call it.

## [Chapter 3: Grades](03_Grades)
This chapter consists of programs that implement a student grading system, which takes the name and intermediate grades of a student (exams and homework), and calculates their final grade. Further chapters continuously expand upon this system.

The most important concept introduced in this chapter is the `vector` type from the standard library, which acts as a container for storing objects of the same type.

Other notable concepts include defining floating-point numbers through the `double` type, passing an object to a function by reference, and error handling.

## [Chapter 4: Records](04_Records)
This chapter extends from [Chapter 3](03_Grades), taking a list of student records and outputting the final grade corresponding to each.

Its main contribution is in demonstating how one can create their own **data structure** to hold variables linked to a single entity.

It also demonstates how one can break their code down into multiple files, by defining their own header files (with file extension `.h` or `.hpp`) containing name declarations (often defined in a separate `.cpp` file) which can be called from another file that needs to access it.

## [Chapter 5: Passing](05_Passing)
This section improves the student grading system, now consisting of a grade threshold used to distinguish between passing and failing students. 

This chapter also consists of a number of other unrelated programs, such as a concordance generator.

It introduces a the `list` type from the standard library, implementing the (doubly) linked list, emphasising its strengths and weaknesses in comparison with the `vector` type.

It also demonstrates the concept of iterators, used to traverse between elements of a sequence of values such as the characters of a `string`.

## [Chapter 6: Analysis](06_Analyis)
This chapter does further work on the student grading system, analysing the student grades by comparing the results of students who did their homework and those who didn't.

But the more important focus of this chapter is in the many different algorithms found in the C++ standard library, used to perform certain tasks on a container, such as finding, copying, removing, modifying and partitioning their elements, possibly storing the results in another container. This reduces the neccessity for writting code which performs similar tasks.

A notable program included in this section is a URL finder, used to extract all the URLs from lines of text, with a number of standard library algorithms being used to implement it.

## [Chapter 7: Maps](07_Maps)
This section focuses entirely on the `maps` standard container, used to hold key-value pairs. It also showcases the concept of recursive functions, as well as how one may define a random number generator.

Programs included in this section include a **cross-refrerence generator**, taking lines of text and lists each word found in it along with the lines they occur on.

Also included is a **sentence generator**, taking a user-defined grammar (as in the Chomsky hierarchy from formal language theory) and generates five random sentences from it.

## [Chapter 8: Generic Functions](08_GenericFunctions)
This section introduces the concept of generic functions, implemented in C++ by what are known as template functions, which act as a family of functions which each differ only by the one or more (arbitrary) types they are made to operate on, called template parameters.

It also expands upon the concept of iterators which themselves related to templates, showing the five different catagories they can fall under, differing in terms of the range of operators that can be applied to them.

## [Chapter 9: Classes](09_Classes)
This section demonstrates how one can create their own type by defining a **class**, made up of both member variables and member functions, with access to them limited in order to hide implementation details from the user and provide a clear interface.

It revisits the student records system, now using a class to store the relevant student data. One of the programs allows the user to choose to either output all the grades together, or to separate them based on whether the student passed or failed.

## [Chapter 10: Pointers and Arrays](10_Pointers&Arrays)
This chapter focuses extensively on the low-level concepts of **pointers** and **arrays**, both carried over from the C programming language. Pointers allow one to hold the memory location of an object, while arrays are similar to the `vector` class type but have a fixed capacity and work very close to memory.

The student records system has been improved by adding grade boundaries which enable the student's grade to be properly ranked in terms of a letter grade.

Another important concept briefly touched upon includes **dynamic memory** allocation and deallocation allowing one to manually control the lifetime of an object or an array in terms of the space assigned to it. 

Also showcased is how one can read text from and write text to a file, and how one can define the `main` function such that it can take arguments from the command-line when running the program.

## [Chapter 11: Template Classes](11_TemplateClasses)
This section expands upon [Chapter 8](08_GenericFunctions) and [Chapter 9](09_Classes) by introducing the concept of **generic classes**, implemented in C++ by **template classes**. They allow one to define class types with members (both data and functions) that depend on one or more arbitrary types limited only by the operations performed on them within the entire class.

To demonstrate how they can be defined, as well as how the standard library uses the mechanism to define its containers, simplified versions of the `vector` and `list` classes (which themselves are template classes) have been implemented under the names `Vec` and `Lst` respectively.

Defined on them are iterators (notably more prominent in the case of `Lst`), as well as special kinds of member functions, overloaded operators, and an object specialised for dynammic memory management (in the case of the `Vec` class only).

As a consequence, many notable concepts that relate to classes have been introduced in this chapter. See notes in the section itself more inforrmation.

## [Chapter 12: Classes as Values](12_ClassesAsValues)
This section focuses on how one may define operators on objects of a class type in a way that enables them to behave more closely as values, that is, they may be converted and assigned to and from other types while keeping its state independent of them. 

In particular, this chapter implements a simplified version of the `string` class, under the name `Str`, relying on the `Vec<char>` class from [Chapter 11](11_TemplateClasses) for memory management and manipulation of its contents. 

On the `Str` class is defined a function that enables a `char*` type (in particular, a pointer to a null-terminated array of characters) to be converted to it automatically. How one can convert a `Str` to a `char*` is also considered, but it is not as simple as one may think.

Other functions deefined include operations for concatenation on `Str` types, which works automatically with a `char*` type due to the conversion function defined for it.