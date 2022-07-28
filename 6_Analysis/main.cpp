#include <algorithm>    // std::find, std::remove, std::stable_partition, std::transform
#include <iostream>     // std::cin, std::cout, std::endl, std::ostream
#include <iterator>     // std::back_inserted
#include <stdexcept>    // std::domain_error
#include <string>       // std::string
#include <vector>       // std::vector

// #include "average.h" 
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::back_inserter;       //using std::ostream;
using std::cin;                 //using std::remove;
using std::cout;                using std::string;
using std::domain_error;        //using std::stable_partition;
using std::endl;                using std::transform;
using std::find;                using std::vector;


// The homework is counted as "all done" if the homework vector is non-empty, and none of its values are zero.
bool did_all_hw(const Student_info& s)
{   
    // If the find() algorithm fails to find a value equal to 0, and at least one grade exists, then all homework is done.
    return ((find(s.homework.begin(), s.homework.end(), 0)) == s.homework.end()) && (s.homework.size() != 0) ;
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
 * This analysis function takes as input a vector of student records,
 * and calculates their final grades, and returns the median of these grades.
 **/
double median_analysis(const vector<Student_info>& students)
{
    vector<double> grades;

    // use transform() to add the values of the students under the grade function to the end of the grades vector
    // (back_inserter() is used to allow values to be appended to grades vector rather than overwriting)
    transform(students.begin(), students.end(),
              back_inserter(grades), grade_aux);
     
    return median(grades);
}

int main()
{
    // students who did and didn't do all their homework
    vector<Student_info> did, didnt;
    Student_info student;

    // prompt the user
    cout << "The goal of this program is to compare the grades of those who did all their homework with those who have not.\n"
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

    cout << "\nComparing the final grades between students who did all homework and those who didn\'t: ";
    // do the analyses
    cout << "\nMedian:" << endl;
    cout << "did     = " << median_analysis(did);
    cout << "didn\'t = " << median_analysis(didnt);

    return 0;
}

/**
 * === ALGORITHMS ===
 * find(iter1, iter2, value) - searches a collecton bounded by iterators [iter1, iter2) and returns the iterator pointing to the 
 *  first occurance of value in the collection. If not found, then iter2 is returned.
 * -------------------
 * transform(iter1, iter2, iter_out, f) - used to apply a function f to a collection of values bound by the iterators [iter1, iter2), 
 *  writting the outputs into another (or the same) collection starting from the position pointed to by iter_out. 
 * -------------------
 * back_inserter(c) - prepares an iterator that points to the end of a collection c, allowing more values to be appended to it.
 **/