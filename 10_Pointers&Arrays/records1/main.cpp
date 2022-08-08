#include <algorithm>
using std::max;
using std::sort;

#include <iomanip>
using std::setprecision;

#include <ios>
using std::fixed;
using std::defaultfloat;
using std::streamsize;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;

#include <map>
using std::map;

#include <stdexcept>
using std::domain_error;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "pad_str.h"
#include "Student_info.h"
#include "trim.h"

// define type mnemonics
typedef string::size_type str_sz;
typedef vector<Student_info>::iterator v_iter;
typedef vector<Student_info>::const_iterator v_citer;


/**
 * Output a sequence of student records bounded by the iterators [b, e),
 * with a padding factor used to improve readibility of output
 **/
void output_records(v_citer b, v_citer e, str_sz maxlen)
{
    // define labels for the output
    string label1 = "STUDENT NAME     "; // allow extra space between labels
    string label2 = "GRADE    ";
    string label3 = "LETTER GRADE";

    // update the padding factor to consider the first label
    maxlen = max(maxlen, label1.size());

    // do formatting for the labels of the output.
    string header_line = label1 + pad_str(label1, maxlen) + label2 + " " + label3;
    string border(header_line.size(), '=');
    cout << border << endl;
    cout << header_line << endl;
    cout << border << endl;

    // create padding space after the grades for the letter grades 
    string letter_pad = pad_str("00.0", label2.size());

    while (b != e) {
        // write the name, padded on the right for neater output
        cout << b->name()
             << pad_str(b->name(), maxlen);

        // compute and write the grade if record is valid.
        if (b->valid()) {
            double final_grade  = b->grade();
            string letter_grade = b->letter_grade();

            // Using fixed-point notation (00.0) write the grade.
            streamsize prec = cout.precision();
            cout << fixed << setprecision(1) << final_grade
                 << setprecision(prec) 
                 << defaultfloat;

            cout << letter_pad << letter_grade << endl;
        }
        // if record not valid (no homework), note this.
        else {
            cout << "(no h/w)" << endl;
        }
        ++b;
    }
    // add a 'footer' line
    cout << border << endl;
}

int main()
{
    // define vector for holding all the student records read.
    vector<Student_info> students;
    // used to hold the current record being read from the input
    Student_info record;

    // record the length of the longest name, for padding the output
    str_sz maxlen = 0;

    // prompt the user to input the records
    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades), "
            "followed by end-of-file: " << endl;

    // read and store all records, and find the length of the longest name
    while (record.read(cin)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // finally output the student records
    output_records(students.begin(), students.end(), maxlen);
    
    return 0;
}
