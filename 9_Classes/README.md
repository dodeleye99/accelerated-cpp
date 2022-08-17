# Chapter 9: Classes

This chapter introduces the concept of **classes**, which allow one to implement their own types to be used in other parts of the program, 
or reused in other programs altogether.

They differ from **data structures** in that classes allow us to combine not only **data values** into a single entity, but also **functions**. 
Together the data and functions are called the members of the class. Each of these members can either be **private** (inaccessable outside the class) or **public** (free accessible outside the class). 

Therefore classes are based around the concept of **encapsulation**, the bundling of data and functions into a single entity, possibly limiting the access to some in order to provide layers of **abstraction** or a simplified interface between the inside and the outside of objects defined by the class.

In C++, they can be defined using either the **`class`** keyword or the **`struct`** keyword, the difference being that the members of the class are private by default when declared with the `class` keyword, while in the case of the `struct` keyword they are public by default.


### Directories of Code:
1)  **records1.cpp** returns to the student grading system established in earlier chapters. It now uses a class rather than a data structure to represent the student records. This makes it possible to define (member) functions specific for each student record for initialising their data elements and for calculating their grades, as well as determining whether a student record is valid due to insufficient grades (in particular, homework) being inputted.

    As usual, the program asks the user to input student grades and outputs the final grade for each student.

### Extensions:
2)  **records2.cpp** expands upon the usual program, by improving the aesthetics of the output, but more importantly giving the user the option to have the output separated into passing grades and failing grades. It does so by asking the user to pick out of two options: output the records the usual way, or to output all the passing grades first, followed by the failing grades.
    
    The class has been modified to only store data need to keep. Instead of storing the students grades inputted by the user, it calculates the final grade upon reading the record and stores it in a member, and uses another member to indicate whether the grades read are valid.

### New Concepts:
* Class types, as explained above.
* Specifying the accessibility of class members using the `public` and `private` keywords.
* Defining class constructors, functions used to initialise an object defined by the class.
* Initialising data members from a class constructor by defining a sequence of **constructor initialisers**, written after a semicolon `:` following the constructor declaration, and before its body `{...}`.
