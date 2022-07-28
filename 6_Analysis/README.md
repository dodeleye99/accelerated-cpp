# Chapter 6: Analysis

An further extension of the student grading system from previous chapters. It explores various algorithms from the C++ standard library and applies them to the grading system to perform analyses on the final grades students achieved, separating the students that did all the homework from those who didn't.

By assumption, any zeros inputted for the homework grades are treated as homework not done. Also, it is assumed that each student should have done at least one homework assignment, and therefore inputting no homework grades for a student is still treaded as homework not done.

### Directories of Code:
1) **analysis1** uses three different grading schemes to compare the grades of students who did all the homework with those who didn't:
    1) the standard grading scheme, which uses the median of the homework grades in calculating the final grade.
    2) the average homework grading scheme, which uses the average of the homework grades in calculating the final grade.
    3) the 'optimistic' grading scheme, which follows the standard grading scheme while only considering homework that was actuall done.
    
    For each analysis representing one of these grading schemes, the program will output the median final grade for each of the two groups.
    
2) **analysis2** revisits the pass-fail system established in Chapter 5. It seeks to consider a second category in the grade analysis: students that passed and students that failed. Thus for each grading scheme analysis, it will generate a table holding the median final grades for each combination of categories (did/didnt $\times$ pass/fail). We will incoprorate the text framing tools established in the extension of Chapter 5 to assist with this.

    It also looks at standard library algorithms that can be used to create further implementations of functions that separate passing and failing students. 
### Extension:

### New Concepts:
* Defining a function which has a function of an established type an argument
* Using the find() function to search for the position of a specific value in a container
* Using transform() function to apply a function to multiple values of a container, specifying where they should be written to.
* Using the back_inserter() function to prepare an iterator poining to the end of a container in order to append new values to it.
* Using remove_copy() to disregard values that match particular value from a container without modifying it, specifying where the remainining values should be written to.
    * Using remove_copy_if() to disregard values that pass a predicate.
    * Using remove_if() to write the remaining values to the same container, thus modifying it.
* Using accumulate() to sum over the values of a container, beginning with an initial value that may not necessarily be 0.
* Using stable_partition() to rearrange the elements of a container into two halves, according to a given predicate.
