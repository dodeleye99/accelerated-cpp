#include <algorithm>    // defines std::sort and std::max
#include <iomanip>      // defines std::setpecision and other manipulators
#include <ios>          // defines std::streamsize
#include <iostream>     // defines std::cin, std::cout, std::endl and std::istream
#include <stdexcept>    // defines std::domain_error
#include <string>       // defines std::string
#include <vector>       // defines std::vector

#include "grade.h"
#include "median.h"         // defines the median function
#include "Student_info.h"   // defines Student_info structure, and compare(), read(), read_hw() functions

using std::cin;             using std::setprecision;          
using std::cout;            using std::sort;
using std::domain_error;    using std::streamsize;
using std::endl;            using std::string; 
using std::max;             using std::vector; 


int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades), "
            "followed by end-of-file: " << endl;

    // read and store all records, and find the length of the longest name
    // Invariant: 'students' contains all the student records read so far
    //            'maxlen' contains the length of the longest name in 'students'       
    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphabetize the records
    sort(students.begin(), students.end(), compare);

    cout << "\nFinal Grades: " << endl;

    // write the names and grades
    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i) {

        // write the name, padded on the right to maxlen + 1 characters. 
        cout << students[i].name
             << string(maxlen + 1 - students[i].name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
            // Indicate whether the student's grade marks a fail.
            if(fgrade(students[i]))
                cout << " (fail)";
        } catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }

    return 0;
}