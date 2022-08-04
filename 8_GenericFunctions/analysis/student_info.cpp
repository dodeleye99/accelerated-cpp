// source file for Student_info-related functions
#include "Student_info.h"

using std::istream; using std::vector;


// compare two students by their name
bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

// read and store midterm and final grades, and homework grades of a single student. 
istream& read(istream& is, Student_info& s) 
{
    // read and store the student's name and midterm and final grades.
    is >> s.name >> s.midterm >> s.final;

    // read and store all the student's homework grades
    read_hw(is, s.homework);

    // (We have the function return the stream instead of a Student_info data structure in order to determine
    //  whether the read was successful or not)
    return is;
}

// read howework grades from an input stream into a vector<int>
istream& read_hw(istream& in, vector<int>& hw) 
{
    // Only proceed to read if there is is a problem with the input stream already.
    if (in) {

        // get rid of previous contents
        hw.clear();

        // read homework grades
        int x;
        // invariant: hw contains all the homework grades read so far
        while (in >> x)
            // append x at the end of the hw vector
            hw.push_back(x);

        // clear the stream so that input will work for the next student.
        in.clear();
    }
    // (We have the function return the stream instead of a vector of the grades in order to determine
    //  whether the read was successful or not)
    return in;
}
