# Chapter 11: Template Classes
In [Chapter 8](../8_GenericFunctions), **function templates** were introduced, allowing one to define a "family of functions", while [Chapter 9](../9_Classes) introduced **classes**, allowing one to define their own type.

This chapter combines both of these concepts together, focusing on what are known as **template classes**, which implement **generic classes**. 

They allow one to create a single definition of a class with a selection of data and function members that together utilise one or more type parameters to define them. This effectively results in a system of classes restricted only by the operations the class members require of the type parameters.

This chapter also covers particular member functions and operators that may be defined on a class, as well as a more flexible method of memory management.
### Directories of Code:
1) [`vec1`](vec1) shows a simplified implementation of the `Vector<T>` template class, under the name [`Vec<T>`](vec1/Vec.h}. It demonstrates how template classes are defined, the special member functions that can be specified on classes, and how one can manage memory effectively. It is used in a program that shows a brief demo for how adding more elements to it can invalidate iterators, due to reallocation of elements.
2) [`vec2`](vec2) adds two more member functions to the class: 
    * `erase`, which deletes the element from the Vec that the given iterator points to.
    * `clear`, which removes all the elements from the Vec.

   This new version of the `Vec` template class is used in a program that demonstates practically how erasing elements from it, or clearing it and         refilling it may cause an iterator to become invalidated.
### Extensions:
3) [`lst`](lst) defines a template class called [`Lst<T>`](lst/Lst.h), a simplified (but still very complicated) implementation of the `List<T>` template class, which implements doubly-linked lists. It demonstates how one may define their own iterator for traversing over the elements of the container, by creating a class that represents it and defining all the necessary operators in accordance to its category (in this case, it is a bi-directonal iterator).
   
   It is used in a program that does numerous tests on its functionality, such as construction, insertion, forward and reverse iterations, and simple sorting.

### New Concepts:
* Defining a template class, producing a family of classes differing only by a set of types associated with each class.
* Defining operators on a class (as class members), which can be overloaded to work with multiple types:
    * `operator=`, which allows one to assign an object to a value using the `=` operator.
    * `operator[]`, used to define an indexing operator to obtain the value at a given relative position in a container that a class may represent.
    * `operator++`, defining an increment operator, used to advances the state of an object by one step (in accordance to some established sequence defined on it).
    * `operator--`, defining a the decrement operator, used to bring an object back to a (theoretical) past state.
    * `operator*`, defining a dereference operator, used to obtain the reference of the value that the object "points" to.
    * `operator->`, defining a member-access operator, used to directly access a member of the value the object "points" to.
    * `operator==`, defining an equality operator, a binary operator that allows one to compare the state of an object with another object, and determine the conditions in which they are considered to be equivalent.
    * `operator!=`, usually the negation of the equality operator.
* Defining special member functions of a class, which will automatically generated (**synthesised**) by the constructor if not explicitly defined in the class:
    * The **copy constructor**, a special constructor that takes constant reference of the same type and uses it to initialise the object.
    * The class **destructor**, used to specify how the object should be destroyed.
    * The **assignment operator** on a class, a special case of `operator=` that takes a constant reference of the same type (representing the right-hand side) and modifies the (left-hand side) object to match its state.
* The differences between the concepts of initialisation (constructing a **new** object) and assignment (modifying a **pre-existing** object to match another one).
* `allocator<T>` objects, which allows for runtime memory management of objects of type `T` in a more flexible, efficient way than using the `new` and `delete` operators, by allowing allocation/deallocation and construction/destruction to be done separately.
* The `explicit` keyword, used to prevent any implicit calls of a particular class constructor, having to instead be written explicitly in order to used.
* The `this` keyword in a class member function, which gives a pointer to the class object.
* The concept of nested/inner classes, a class defined within a class, able to access every member of its outer class.
* Defining an iterator on a container class.
* Reverse iterators, which traverse over a sequence of values in reverse order, by swapping the uses of the increment and decrement operators
   *  The `std::reverse_iterator<Iter>` template class, used to make a given iterator function like a reverse iterator.
* The `friend` keyword, used to allow the private members of a class to be accessible to another particular class.
