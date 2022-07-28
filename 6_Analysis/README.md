# Chapter 6: Analysis

An further extension of the student grading system from previous chapters. It explores various algorithms from the C++ standard library and applies them to the grading system to perform analyses on the final grades students achieved, separating the students that did all the homework from those who didn't.

By assumption, any zeros inputted for the homework grades are treated as homework not done. Also, it is assumed that each student should have done at least one homework assignment, and therefore inputting no homework grades for a student is still treaded as homework not done.

### Directories of Code:
1) **analysis1** uses three different grading schemes to compare the grades of students who did all the homework with those who didn't:
    1) the standard grading scheme, which uses the median of the homework grades in calculating the final grade.
    2) the average homework grading scheme, which uses the average of the homework grades in calculating the final grade.
    3) the 'optimistic' grading scheme, which follows the standard grading scheme while only considering homework that was actuall done.
    
    For each analysis representing one of these grading schemes, the program will output the median final grade for each of the two groups.
    
2) **analysis2**
### Extension:

### New Concepts:
* Defining a function which has a function of an established type an argument
* Using the find() function to search for the position of a specific value in a container
* Using transform() function to apply a function to multiple values of a container, specifying where they should be written to.
* Using the back_inserter() function to prepare an iterator poining to the end of a container in order to append new values to it.
* Using remvoe_copy() to extract values of a container without modifying it, specifying specifying where they should be written to.
