# Chapter 3: Grades

The source code is for programs which implement a student grading system. 
After greeting the user in the same way as Chapters 1 and 2, it asks for the user's exam grades (midterm and final), and then for their homework grades.
These grades are then used to calculate a final grade for the user.

The final grade for the student is calculated as the sum of 20% of the midterm exam grade, 40% of the final exam grade, and 40% of the _average_ homework grade. 

### Code:
1) **grades1.cpp** does the above.
2) **grades2.cpp** uses a vector to store the homework grades as they are inputted. In the grade calculation, instead of using the average, it now uses the _median_ of the homework grades. It also does input validation, ending the program early if an insufficient number of grades (such as no homework) is inputted.
3) **grades3.cpp** breaks the code into more parts, and goes into more depth with validating the user's input by catching errors that would be caused by not inputting any homework grades (or invalid exam grades). It is also written in light of the next chapters, where the grades of _multiple_ students are inputted.

### New Concepts:
* reading multiple inputs from the user.
* floating-point 'double' numbers, for representing non-integer or decimal numbers.
* prescision manipulator for decimals.
* the vector container, used to hold a collection of values of the same type.
* passing a reference of a variable (rather than a copy as by default) to a function, allowing it to be modified in a different scope.
* catching errors.
* input stream handling.
