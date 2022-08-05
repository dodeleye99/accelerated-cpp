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

    // update the padding factor to consider the first label
    maxlen = max(maxlen, label1.size());

    // do formatting for the labels of the output.
    string header_line = label1 + pad_str(label1, maxlen) + label2;
    string border(header_line.size(), '=');
    cout << border << endl;
    cout << header_line << endl;
    cout << border << endl;

    while (b != e) {
        // write the name, padded on the right for neater output
        cout << b->name()
             << pad_str(b->name(), maxlen);

        // compute and write the grade if record is valid.
        if (b->valid()) {
            double final_grade = b->grade();
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
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

/**
 * Output sequence of student records bound by iterators [b, e),
 * Dividing output based on whether they passed or failed.
 **/
void output_passfail(v_iter b, v_iter e, str_sz maxlen)
{   
    // Modify the sequence, 'extracting' the fails by moving them to
    //  the front. Retrive iterator pointing to the front of the 'pass' half.
    v_iter c = extract_fails(b, e);

    // Output both parts
    cout << "\n--- STUDENTS WHO PASSED ---" << endl;
    output_records(c, e, maxlen);
    cout << "\n--- STUDENTS WHO FAILED ---" << endl;
    output_records(b, c, maxlen);

}

/**
 * Reads the option made by the user, to determine how the records should be outputted:
 * 
 * Option 1: Output records in usual way, line by line.
 * Option 2: Output the records in two parts, one for the passing students and the other 
 *           for the failing students.
 **/
string read_option()
{   
    // prompt the user to choose their option.
    cout << "How you would like to output the student records?" << endl;
    cout << "1\t" << "ALL" << endl;
    cout << "2\t" << "PASS + FAIL" << endl;
    cout << "\nInput the digit representing your choice: ";
    
    /* Read and validate the input user's input */

    // to hold the user's input
    string input;
    // to hold a flag determining if valid input was entered by the end of one loop.
    bool invalid_input;

    // make sure the user inputs a correct option (only giving up if end-of-file entered) */
    do
    {   
        // read the entire line as user input, stripping any space.
        getline(cin, input);
        input = trim(input);

        cout << endl;

        invalid_input = false;

        // Check whether input is a valid option.
        if (input != "1" && input != "2")
        {   
            // tell user their input was invalid, and continue the loop.
            cout << "Invalid option. Enter again: ";
            invalid_input = true;
        }
    }
    while (invalid_input && cin);

    return input;
}

int main()
{
    // read the user's option.
    string option = read_option();

    // define vector for holding all the student records read.
    vector<Student_info> students;
    // used to hold the current record being read from the input
    Student_info record;

    // define labels for the output
    string label1 = "STUDENT NAME     "; // allow extra space between labels
    string label2 = "GRADE    ";
    str_sz maxlen = label1.size();

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


    // Evaluate the option that was inputted
    if (option == "1")
    {
        output_records(students.begin(), students.end(), maxlen);
        
    }
    else if (option == "2")
    {
        output_passfail(students.begin(), students.end(), maxlen);
    }
    // This point should be unreachable, but output an appropriate nevertheless 
    else
    {
        cout << "Option does not exist." << endl;
    }
    
    return 0;
}
