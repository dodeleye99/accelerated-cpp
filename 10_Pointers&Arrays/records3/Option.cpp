#include <algorithm>
using std::max;

#include <ios>
using std::fixed;
using std::defaultfloat;
using std::streamsize;

#include <iomanip>
using std::setprecision;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ostream;

#include <map>
using std::map;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "Option.h"
#include "Student_info.h"
#include "pad_str.h"
#include "trim.h"


Option input_option(const Option_map& opts, const string& prompt="")
{   
    // if one is entered, prompt the user to choose their option.
    cout << prompt << endl;

    // output the options to choose from.
    for (Option_map::const_iterator iter = opts.begin(); iter != opts.end(); ++iter)
    {
        cout << iter->first << "\t" << iter->second.label << endl;
    }
    cout << endl;
    
    // to hold the user's input
    string input;
    // to point to the user's chosen option based on their input if valid
    Option_map::const_iterator opt_input;

    // to be used as a flag determining if valid input was entered by the end of one loop.
    bool invalid_input;

    // make sure the user inputs a correct option (only giving up if end-of-file entered)
    do
    {   
        // read the entire line as user input, stripping any space.
        getline(cin, input);
        input = trim(input);

        // find the option that corresponds to the user's input 
        opt_input = opts.find(input);

        cout << endl;

        invalid_input = false;

        // check whether input is a valid option, determined by whether the search for the
        // corresponding option was successful
        if (opt_input == opts.end())
        {   
            // tell user their input was invalid, and continue the loop.
            cout << "Invalid option. Enter again: ";
            invalid_input = true;
        }
    }
    while (invalid_input && cin);

    // one input is valid, output the corresponding option.
    return opt_input->second;   
}

/**
 * (The overarching student record outputting function)
 * Writes to an output file a sequence of student records (name, numerical grade, and letter grade if lg=true)
 * bounded by the iterators [b, e), with a padding factor used to improve readibility of output.
 **/
void output_records(ostream& out, v_iter b, v_iter e, str_sz maxlen, bool lg=true)
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
            if (lg) {
                out << letter_pad << letter_grade;
            }
            out << endl;
            
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

// OPTION #1: Output all student records together
void output_records_std(ostream& out, v_iter b, v_iter e, str_sz maxlen)
{
    output_records(out, b, e, maxlen);
}

// OPTION #2: Output passing students and failing students separately.
void output_records_passfail(ostream& out, v_iter b, v_iter e, str_sz maxlen)
{   
    // Modify the sequence, 'extracting' the fails by moving them to
    //  the front. Retrive iterator pointing to the front of the 'pass' half.
    v_iter c = extract_fails(b, e);

    // Output both parts
    out << "\n--- STUDENTS WHO PASSED ---" << endl;
    output_records(out, c, e, maxlen);
    out << "\n--- STUDENTS WHO FAILED ---" << endl;
    output_records(out, b, c, maxlen, false); // 'false' to not write letter grades (would be redundant here)

}
