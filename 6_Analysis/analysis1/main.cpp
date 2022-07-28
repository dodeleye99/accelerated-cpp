#include <algorithm>    // std::find, std::remove_copy, std::transform
#include <iostream>     // std::cin, std::cout, std::endl
#include <iterator>     // std::back_inserter
#include <stdexcept>    // std::domain_error
#include <string>       // std::string
#include <vector>       // std::vector

#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::back_inserter;       using std::find;
using std::cin;                 using std::remove_copy;
using std::cout;                using std::string;
using std::domain_error;        using std::transform;
using std::endl;                using std::vector;


// The homework is counted as "all done" if the homework vector is non-empty, and none of its values are zero.
bool did_all_hw(const Student_info& s)
{   
    // If the find() algorithm fails to find a value equal to 0, and at least one grade exists, then all homework is done.
    return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end()) && (!s.homework.empty()) ;
}

/**
 * This acts as an auxilirary or extention of the grade() function.
 * If there is a problem calculating the grade (likely due to no homework grades inputted), 
 *  it puts down the homework grade used for calculating the final grade as zero.
 **/
double grade_aux(const Student_info& s)
{
    try {
        return grade(s);
    } catch (domain_error) {
        return grade(s.midterm, s.final, 0);
    }
}

/**
 * This acts as an auxilirary or extention of the average_grade() function.
 * (The average of the student's homework grades is used in the final grade calculation rather than the median.)
 **/
double average_grade_aux(const Student_info& s)
{
    try {
        return average_grade(s);
    } catch (domain_error) {
        return grade(s.midterm, s.final, 0);
    }
}

/**
 * This function follows the standard grading scheme (uses median homework grade), but only considers non-zero homework grades
 * in the calculation.
 **/
double optimistic_grade(const Student_info& s)
{
    // form a vector that will hold only non-zero homework grades.
    vector<int> nonzero_hw;
    
    // add all values not equal to 0 to the nonzero_hw vector. i.e. extract all values that are non-zero.
    // (WITHOUT modifying the original homework vector, hence the "copy")
    remove_copy(s.homework.begin(), s.homework.end(),
                back_inserter(nonzero_hw), 0);
    if(nonzero_hw.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero_hw));
}

/**
 * The mainline analysis function, taking as input a vector of student records,
 * and calculates their final grades using a given grading scheme, and returns the median of these grades.
 **/
double analysis(const vector<Student_info>& students, double grading_scheme(const Student_info&))
{
    vector<int> grades;
    transform(students.begin(), students.end(),
              back_inserter(grades), grading_scheme);

    return median(grades);
}
/**
 * This procedure is used to output the results of an analysis comparing the final grades of students who did all 
 * their homework with students who have not, under a given grading scheme
 **/
void write_analysis(const string title, double grading_scheme(const Student_info&),
                    const vector<Student_info>& did_hw, const vector<Student_info>& didnt_hw)
{
    cout << "\n(" << title << ") - median final grade of students who:" << endl;
    cout << "Did all homework:       " << analysis(did_hw, grading_scheme) << endl;
    cout << "Didn't do all homework: " << analysis(didnt_hw, grading_scheme) << endl;
}

int main()
{
    // students who did and didn't do all their homework
    vector<Student_info> did, didnt;
    Student_info student;

    // prompt the user
    cout << "This program compares the final grades of those who did all their homework with those who have not.\n"
         << "Please enter the records of each student (name, midterm and final exam grades, homework grades), "
            "followed by end-of-file:" 
         << endl;

    // read all the records, separating them based on whether all homework was done
    while (read(cin, student)) {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }

    // check that both groups contain data, i.e. verify that the analysess will show us something
    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    }
    if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    // do the analyses
    cout << "\nComparing the final grades between students who did all homework and those who didn\'t: " << endl;

    // Analysis #1: standard grading scheme - incorporates the median of homework grades in the calculation
    write_analysis("Standard grading scheme", grade_aux, did, didnt);

    // Analysis #2: average homework grading scheme - incorporates the average of homework grades in the calculation
    write_analysis("Average homework grading scheme", average_grade_aux, did, didnt);

    // Analysis #3: "optimistic" homework grading scheme - uses standard grading scheme, but ignores homework not done.
    write_analysis("Turned-in homework grading scheme", optimistic_grade, did, didnt);
    
    return 0;
}
/**
 * === ALGORITHMS ===
 * find(iter1, iter2, value) - searches a container bounded by iterators [iter1, iter2) and returns the iterator pointing to the 
 *  first occurance of value in the collection. If not found, then iter2 is returned.
 * -------------------
 * transform(iter1, iter2, iter_out, f) - used to apply a function f to a collection of values bound by the iterators [iter1, iter2), 
 *  writting the outputs into another (or the same) collection starting from the position pointed to by iter_out. 
 * -------------------
 * back_inserter(c) - prepares an iterator that points to the end of a container c, allowing more values to be appended to it.
 * -------------------
 * remove_copy(iter1, iter2, iter_out, val) - traverses over a container bounded by iterators [iter1, iter2) and, without deleting 
 *  values from the original container (hence the "copy"), extracts all values != val to a new (or the same) container 
 *  starting from the position pointed to by iter_out.
 **/
