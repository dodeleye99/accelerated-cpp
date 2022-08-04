# Chapter 9: Classes

This chapter introduces the concept of **classes**, which allow one to implement their own types to be used in other parts of the program, 
or reused in other programs altogether.

They differ from **data structures** in that classes allow us to combine not only **data values** into a single entity, but also **functions**. 
Together the data and functions are called the members of the class. Each of these members can either be **private** (inaccessable outside the class) or **public** (free accessible outside the class). 

Therefore classes are based around the concept of **encapsulation**, the bundling of data and functions into a single entity, possibly limiting the access to some in order to provide layers of **abstraction** or a simplified interface between the inside and the outside of objects defined by the class.

In C++, they can be defined using either the **'class'** keyword or the **'struct'** keyword, the difference being that the members of the class are private by default when declared with the 'class' keyword, while in the case of the 'struct' keyword they are public by default.


### Directories of Code:
1)  **records1.cpp** returns to the student grading system established in earlier chapters. It now uses a class rather than a data structure to represent the student records, which makes it possible to define (member) functions specific for each student record for initialising their data elements and for calculating their grades, as well as determining whether a student record is valid due to insufficient grades (in particular, homework) being inputted.

### Extensions:

### References:

### New Concepts:
* Class types, as explained above.
* Specifying the accessibility of class members using the **public** and **private** keywords.
* Defining class constructors, functions used to initialise an object defined by the class. 
