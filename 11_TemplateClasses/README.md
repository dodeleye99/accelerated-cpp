# Chapter 11: Template Classes
In [Chapter 8](../8_GenericFunctions), **function templates** were introduced, allowing one to define a "family of functions", while [Chapter 9](../9_Classes) introduced **classes**, allowing one to define their own type.

This chapter combines both of these concepts together, focusing on what are known as **template classes**, which implement **generic classes**. 

They allow one to create a single definition of a class with a selection of data and function members that together utilise one or more type parameters to define them. This effectively results in a system of classes restricted only by the operations the class members require of the type parameters.

### Directories of Code:

### Extensions:
    
### References:

### New Concepts:
* Defining a template class, producing a family of classes differing only by a set of types associated with each class.
* Defining operators on a class.
* The copy constructor, a special constructor that takes constant reference of the same type and uses it to initialise the object.  
* Defining the class destructor, a special member function used to specify how the object should be destroyed.
* Defining the assignment operator on a class, a special case of `operator=` that takes a constant reference of the same type (representing the right-hand side) and modifies the (left-hand side) object to match its state.
* Defining an indexing operator (`operator[]`) on a class.
* The `explicit` keyword, to prevent using a class constructor for automatic conversions.
