# Chapter 12: Classes as Values

We have briefly seen in previous chapters how objects of **class types** can be made to function like **values**, that is, retaining an **independent** state during operations, unrelated to the state of any other objects involved.

In particular, the **copy constructor** and **assignment operator**, which every class will have defined (synthesised by the compiler if the user does not define them) allows us to "set" an object (whether new or pre-existent) to another one using the `=` symbol. If properly defined, the object can be made independent of the object used to set it, thus acting like a value.

Previous chapters show extensively that **built-in types** generally behave the same way, with a typical example being the `int` type. One must use a **reference** if they wish to define a variable that is linked to the state of another variable. 

But even moreso, built-in types are capable of undergoing **conversion** from one type to another, done automatically by the compiler when an operator or function requires specific types. For instance, when using the addition operartor `+` to add an `int` and a `double`, the `int` is automatically converted to a `double` to complete the operation. Another example is built-in **arrays** introduced in [Chapter 10](../10_Pointers&Arrays), which are generally converted to a **pointer** its the first element whenever they are used as a value, acting as a **random-access iterator** over the array elements.

This chapter explores in greater depth all the different methods in defining and carefully designing operators that allow class objects to behave as values, including how one can transform an object from one class to another.

### Directories of Code:
1) [`str1`](str1) consists of a simplified vesion of the `std::string` class, under the name [`Str`](str1/Str.h), acting as an extension of the `Vec` template class defined in [Chapter 11](../11_TemplateClasses), particularly `Vec<char*>`. It consists of operations specific to strings, including concatenation, stream input and stream output, as well as a constructor that acts as a conversion from a `char*` object to a `Str` object. 

    The directory also constists of a program demonstating its use, while showing cases where the automatic convertions are carried out.
    
2) [`str2`](str2) improves upon the `Str` class. It adds three functions used by the `std::string` class for explicit conversion to a `char*` object pointing to a character array: 
    * `c_string()`, giving the user a copy of the `Str` in the form of a null-terminated character array,
    * `data()`, same as `c_string()`, but the array is not necessarily null-terminated
    * `copy()`, takes a pointer to a character array from the user, and writes the characters in a specified index range from the `Str` object to it. 
    
    The `std::string` class does not provide an implicit conversion, because there is no single way it can be done without drawbacks or potential dangers from occuring, especially since the resulting character array will be dynamic (see comments above data member `c` in [`Str.h`](str2/Str.h)).

    The relational operators (`<`, `>`, `<=`, `>=`), equality operator (`==`) and the inequality operator (`!=`) have also been defined to take `Str`                   objects and compare them based on the lexographical ordering of their characters, or whether their character sequences match exactly.
    
    To test some of the new operations, the class is used on a new version of the student records program. This time it outputs each record in a separate file based on the name of the student. Each file contains the following:
    *  student name,
    *  final grade,
    *  letter grade,
    *  register position (based on the alphabetical ordering of their name),
    *  grade rank (out of entire records read, based on their final grade).
    
    A few operations have also been added for the `Student_info` class:
    * conversion to `double` (based on final grade)
    * conversion to `bool` (based on validity of record)
    * comparing two `Student_info` objects to determine which one has the highest grade.
    
### Extensions:

### New Concepts:
* **User-defined conversions**, which tell the compiler how to transform an object from one class to another, doing so automatically when required.
* Defining constructors that act as user-defined conversions.
* **Friendships**, allowing classes (see [Chapter 11](../11_TemplateClasses)) and functions to access private members of the class, by declaring them with the `friend` keyword in the class.
* Explicit **conversion operators**, used to an object from its type to a target type.
* `void*` pointers, also known as **universal pointers**, capable of pointing to any type of object, but must be converted to a particular type in order to be dereferenced.
* The importance of the `explicit` keyword for constructors that may otherwise be used for automatic conversions that give unwanted behavior (see also [Chapter 11](../11_TemplateClasses)).
