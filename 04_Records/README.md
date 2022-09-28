# Chapter 4: Records

An extension of the grading system established in Chapter 3. Rather than only the grade of one student calculated, the program allows multiple student records to be inputted by the user, and calculates the final grade for each one. It then neatly outputs in alphabetical order each student's name along with their final grade.

The data inputted for each student are grouped together into a new data structure called Student_info, and placed into a vector representing the data of each student. 

The input grades are now restricted to integers rather than decimals, to prevent the strange behaviour illustrated and explained [here](https://stackoverflow.com/questions/44688567/why-is-iostream-cutting-off-the-first-letter-in-certain-words).

### Directories of Code:
1) [`records1`](records1) containing only **main.cpp** does as explained above.
2) [`records2`](records2) breaks the source code down into multiple files to make it more organised and easier to find particular code. The source code is now located in a new subdirectory called `src`. 

### Extension:
3) [`squares`](squares) does further experimentation with neatly writting a table of results. It computes the squares of 0 to any given positive integer.

### New Concepts:
* defining `struct` types, used to group data values to form a data structure, so that it can be treated as a single entity.
* using the `max` algorithm to find the maximum value of a data set.
* sorting struct types by specifying the comparison function used to define the ordering.
* modular programming, breaking down source code into separate components.
* header files, containing name declarations of data values and types, such as functions and structures, to be defined in a separate, corresponding C++ source code file.
* using basic maths operatons from the `<cmath>` standard header. 
* the `break` statement, used to terminate the current loop.