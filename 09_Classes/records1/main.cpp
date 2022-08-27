#include <algorithm>
using std::max;
using std::sort;

#include <iomanip>
using std::setprecision;

#include <ios>
using std::streamsize;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <stdexcept>
using std::domain_error;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "pad_str.h"
#include "Student_info.h"


int main()
{
    // define vector for holding all the student records read.
    vector<Student_info> students;
    // used to hold the current record being read from the input
    Student_info record;

    // mark the length of maximum student name for padding
    string::size_type maxlen = 0;

    // prompt the user
    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades), "
            "followed by end-of-file: " << endl;

    // read and store all records, and find the length of the longest name
    while (record.read(cin)) {
        
        // record the maximum width of all names for the sake of padding when we start outputting results
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
    
    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    cout << endl;
    // write the names and grades
    for (vector<Student_info>::const_iterator it = students.begin(); it != students.end(); ++it) {
        
        // write the name, padded on the right for neater output
        cout << it->name()
             << pad_str(it->name(), maxlen);

        // compute and write the grade
        try {
            double final_grade = it->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                << setprecision(prec) << endl;
        // catch error due to insufficient homework grades
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
