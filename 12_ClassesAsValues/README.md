# Chapter 12: Classes as Values

We have briefly seen in previous chapters how objects of **class types** can be made to function like **values**, that is, retaining an **independent** state during operations, unrelated to the state of any other objects involved.

In particular, the **copy constructor** and **assignment operator**, which every class will have defined (synthesised by the compiler if the user does not define them) allows us to "set" an object (whether new or pre-existent) to another one using the `=` symbol. If properly defined, the object can be made independent of the object used to set it, thus acting like a value.

Previous chapters show extensively that **built-in types** generally behave the same way, with a typical example being the `int` type. One must use a **reference** if they wish to define a variable that is linked to the state of another variable. 

But even moreso, built-in types are capable of undergoing **conversion** from one type to another, done automatically by the compiler when an operator or function requires specific types. For instance, when using the addition operartor `+` to add an `int` and a `double`, the `int` is automatically converted to a `double` to complete the operation. Another example is built-in **arrays** introduced in [Chapter 10](../10_Pointers&Arrays), which are generally converted to a **pointer** its the first element whenever they are used as a value, acting as a **random-access iterator** over the array elements.

This chapter explores in greater depth all the different methods in defining and carefully designing operators that allow class objects to behave as values, including how one can transform an object from one class to another.

### Directories of Code:

### Extensions:

### New Concepts:
* **User-defined conversions**, which tell the compiler how to transform an object from one class to another, doing so automatically when required.
* Defining constructors that act as user-defined conversions.
* **Friendships**, allowing classes (see [Chapter 11](../11_TemplateClasses)) and functions to access private members of the class, by declaring them with the `friend` keyword in the class.
* Explicit **conversion operators**, used to an object from its type to a target type.
* `void*` pointers, also known as **universal pointers**, capable of pointing to any type of object, but must be converted to a particular type in order to be dereferenced.
* The importance of the `explicit` keyword for constructors that may otherwise be used for automatic conversions that give unwanted behavior (see also [Chapter 11](../11_TemplateClasses)).
