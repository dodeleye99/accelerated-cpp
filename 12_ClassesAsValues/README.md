# Chapter 11: Classes as Values
We have briefly seen in previous chapters how objects of class types can be made to function as values.

For example, the **assignment operator** and **copy constructor**, which every class will have defined (synthesised by the compiler if the user does not define them) allows us to "set" an object (wherther new or pre-existent) to another one using the `=` symbol. If properly defined, the object can be made independent of the object used to set it.

One may also define operators on classes to make them act like values. For example, `Lst::Iterator` class we defined for the `Lst` template class. Any object of that class type can be incremented `++` and decremented `--`, very similarly to pointers and `int` types.

In this chapter we explore in greater depth all the different methods in defining and carefully designing operator thah allow class objects to behave as values, including how one can transform an object from one class to another.

### Directories of Code:

### Extensions:

### New Concepts:
