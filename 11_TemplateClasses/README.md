# Chapter 11: Template Classes
In [Chapter 8](../8_GenericFunctions), **function templates** were introduced, allowing one to define a "family of functions", while [Chapter 9](../9_Classes) introduced **classes**, allowing one to define their own type.

This chapter combines both of these concepts together, focusing on what are known as **template classes**, which implement **generic classes**. 

They allow one to create a single definition of a class with a selection of data and function members that together utilise one or more type parameters to define them. This effectively results in a system of classes restricted only by the operations the class members require of the type parameters.

This chapter also covers particular member functions and operators that may be defined on a class, as well as a more flexible method of memory management.
### Directories of Code:
* [vec1](vec1) shows a simplified implementation of the `Vector<T>` template class. It demonstrates how template classes are defined, the special member functions that can be specified on classes, and how one can manage memory effectively.
### Extensions:
    
### References:

### New Concepts:
* Defining a template class, producing a family of classes differing only by a set of types associated with each class.
* Defining operators on a class (as class members).
    *  `operator=`, which allows one to assign an object to a value using the `=` operator.
    *  `operator[]`, used to define an indexing operator to obtain the value at a given relative position in a container that a class may represent.
* Defining special member functions of a class, which will automatically generated (**synthesised**) by the constructor if not explicitly defined in the class:
    * The **copy constructor**, a special constructor that takes constant reference of the same type and uses it to initialise the object.
    * The class **destructor**, used to specify how the object should be destroyed.
    * The **assignment operator** on a class, a special case of `operator=` that takes a constant reference of the same type (representing the right-hand side) and modifies the (left-hand side) object to match its state.
* The differences between the concepts of initialisation (constructing a **new** object) and assignment (modifying a **pre-existing** object to match another one).
* `allocator<T>` objects, which allows for runtime memory management of objects of type `T` in a more flexible, efficient way than using the `new` and `delete` operators, by allowing allocation/deallocation and construction/destruction to be done separately.
* The `explicit` keyword, used to prevent any implicit calls of a particular class constructor, having to instead be written explicitly in order to used.
* The `this` keyword in a class member function, which gives a pointer to the class object.
