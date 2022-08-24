#include <algorithm>
using std::max;
using std::sort;

#include <fstream>
using std::ifstream;
using std::ofstream;

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
using std::istream;
using std::ostream;

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
 * Writes to an output file a sequence of student records (name, numerical grade, letter grade)
 * bounded by the iterators [b, e), with a padding factor used to improve readibility of output
 **/
void output_records(ofstream& out, v_citer b, v_citer e, str_sz maxlen)
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
    out << border << endl;
    out << header_line << endl;
    out << border << endl;

    // create padding space after the grades for the letter grades 
    string letter_pad = pad_str("00.0", label2.size());

    while (b != e) {
        // write the name, padded on the right for neater output
        out << b->name()
             << pad_str(b->name(), maxlen);

        // compute and write the grade if record is valid.
        if (b->valid()) {
            double final_grade  = b->grade();
            string letter_grade = b->letter_grade();

            // Using fixed-point notation (00.0) write the grade.
            streamsize prec = out.precision();
            out << fixed << setprecision(1) << final_grade
                 << setprecision(prec) 
                 << defaultfloat;

            out << letter_pad << letter_grade << endl;
        }
        // if record not valid (no homework), note this.
        else {
            out << "(no h/w)" << endl;
        }
        ++b;
    }
    // add a 'footer' line
    out << border << endl;
}

/**
 * Reads from an input stream student grade data and adds it to the end of a
 * vector. It also takes a value (by reference) representing the size of the 
 * student name read so far, in order to updated and used for padding the output
 * later.
 **/
void read_input(istream& in, vector<Student_info>& students, str_sz& maxlen)
{   
    Student_info record;

    while (record.read(in)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
}

// 1st argument: input file
// 2nd argument: output file
// Further arguments: extra input files
int main(int argc, char** argv)
{   
    // define vector for holding all the student records read.
    vector<Student_info> students;
    // used to hold the current record being read from the input
    Student_info record;
    
    // record the length of the longest name, for padding the output
    str_sz maxlen = 0;

    // represents the number of files that could be opened
    int success_count = 0;
    // represents the number of files that could not be opened
    int fail_count = 0;

    // represents the directory (name) of the output file
    string output_dir;

    // determines whether no input arguments were entered, which indicates
    // that the user will enter the data directly from standard input.
    bool manual_mode = (argc == 1);

    // read through every command-line argument
    for(size_t i = 1; i != argc; ++i) {
        // The non-second input arguments represent input fils to
        // read student records from 
        if (i != 2) {
            // Open the output file (or create a new one)
            ifstream in_file(argv[i]);
            // If it was successfully opened, read it.
            if(in_file) {
                read_input(in_file, students, maxlen);
                ++success_count;
            }
            // If not, give an appropriate message.
            else {
                cout << "Could not open \'" << argv[i] << "\'." << endl;
                ++fail_count;
            }
        }
    }
    // The second input argument represents an output file to
    // write the student final grades to. If not entered, use a default one.
    output_dir =  argc > 2 ? argv[2] : "out.txt";
    
    // If no files were entered, have the data entered the usual way
    // from the standard input stream (i.e. "manual mode").
    if(manual_mode) {
        // prompt the user to input the records directly
        cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades)"
                "directly, followed by end-of-file: " << endl;
        // read and store all records, and seek the length of the longest name
        read_input(cin, students, maxlen);
    }
    // If in "input file mode", but the files entered could not be opened, 
    // give an appropriate message and end the program.
    else if (success_count == 0) {
        cout << "None of the input files could be opened.\n" << endl;
        return fail_count;
    }

    // Open the output file (or create a new one)
    ofstream output_file(output_dir.c_str());

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // if no records were entered (successfully), only give an approprate message.
    if (students.empty()) {
        cout << "No records entered." << endl;
    }
    // otherwise, output the student records finally.
    else {
        output_records(output_file, students.begin(), students.end(), maxlen);
        cout << "Output written to \'" << output_dir << "\'." << endl;
    }
    return fail_count;
}
