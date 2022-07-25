#include <algorithm>    // defines std::sort and std::max
#include <iomanip>      // defines std::setpecision and other manipulators
#include <ios>          // defines std::streamsize
#include <iostream>     // defines std::cin, std::cout, std::endl and std::istream
#include <list>         // defines std::list
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
using std::list;


// write names and grades from a list of students
void output_grades(const list<Student_info>& students, const string::size_type pad_factor)
{
    for (list<Student_info>::const_iterator iter = students.begin(); iter != students.end(); ++iter)
    {
        // write the name, padded on the right to maxlen + 1 characters. 
        cout << (*iter).name
             << string(pad_factor + 1 - (*iter).name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(*iter);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }
}


int main()
{
    list<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades),"
            "followed by end-of-file: " << endl;

    // read and store all records, and find the length of the longest name
    // Invariant: 'students' contains all the student records read so far
    //            'maxlen' contains the length of the longest name in 'students'       
    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    
    // extract the failing students from the list of students
    // the students list will then only contain those who passed.
    list<Student_info> fails = extract_fails(students);

    // alphabetize the records
    students.sort(compare);
    fails.sort(compare);
    
    // first output the names and grades of the students that passed
    cout << "\nPassing Students: " << endl;
    output_grades(students, maxlen);

    // then output the names and grades of the students that failed
    cout << "\nFailing Students: " << endl;
    output_grades(fails, maxlen);

    return 0;
}