# Chapter 3: Grades

The source code is for programs which implement a student grading system. 
After greeting the user in the same way as Chapters 1 and 2, it asks for the user's exam grades (midterm and final), and then for their homework grades.
These grades are then used to calculate a final grade for the user.

The final grade for the student is calculated as the sum of 20% of the midterm exam grade, 40% of the final exam grade, and 40% of the _average_ homework grade. 

### Code:
1) **grades1.cpp** does the above.
2) **grades2.cpp** uses a vector to store the homework grades as they are inputted. In the grade calculation, instead of using the average, it now uses the _median_ of the homework grades. It also does input validation, ending the program early if an insufficient number of grades (such as no homework) is inputted.
3) **grades3.cpp** breaks the code into more parts, and goes into more depth with validating the user's input by catching errors that would be caused by not inputting any homework grades (or invalid exam grades). It is also written in light of the next chapters, where the grades of _multiple_ students are inputted.

### Extension:
4) **words.cpp** does further experimentation with vector containers. It takes a sequence of words from the user as input, and returns the number of times each distinct word occurs.
4) **quartiles.cpp** does further experimentation regarding the calculations on a sequence of numbers. It takes a sequence of integers as user input, and outuputs its quartiles, including the minimum (0%), lower quartile (25%), median (50%), upper quartile (75%), and maximum (100%).

### New Concepts:
* reading multiple inputs from the user.
* floating-point 'double' numbers, for representing non-integer or decimal numbers.
* the conditional (?) operator.
* the divide operator, which has behaviour depending on the types of the numbers performed on (integer or decimal).
* the modulus operator, computing the remainder after division between integers.
* prescision manipulator for decimals.
* the vector container, used to hold a collection of values of the same type.
* indexing to access elements of a container.
* sorting elements of a container.
* iterators objects, pointing to the start and the end of a container.
* passing a reference of a variable (rather than a copy as by default) to a function, allowing it to be modified in a different scope.
* catching errors and initialising error objects.
* input stream handling.
* type definitions, which act as a synonym for an establsihed type in a scope, for quicker and neater typing.
