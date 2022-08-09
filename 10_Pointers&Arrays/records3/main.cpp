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

#include "Option.h"
#include "pad_str.h"
#include "Student_info.h"
#include "trim.h"


/**
 * Reads from an input stream student grade data and adds it to the end of a
 * vector. It also takes a value (by reference) representing the size of the 
 * student name read so far, in order to updated and used for padding the output
 * later.
 **/
void read_input(istream& in, vector<Student_info>& students, string::size_type& maxlen)
{   
    Student_info record;

    while (record.read(in)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }
}

/**
 * Gets the user to input an option for how to output the student grades:
 * 
 * Option 1: Output records in usual way (all of them together, line by line).
 * Option 2: Output the records in two parts, one for the passing students and the other 
 *           for the failing students.
 **/
Option choose_option()
{
    /**
     * Define a map to hold each option, with a key representing the text the user should
     * type to enter it.
     **/
    Option_map op_map;

    // Option o1;
    // o1.label = "ALL";
    // o1.f = &output_records_std;
    // op_map["1"] = o1;

    // Option o2;
    // o2.label = "PASS + FAIL";
    // o2.f = &output_records_passfail;
    // op_map["2"] = o2;

    /**
     * =========================
     * HOW FUNCTION POINTES WORK
     * =========================
     * Note that we pass the name of the output functions to the Option constructor.
     * In reality, we are implicitly passing a POINTER to these functions.
     * Each name as automatically given an address-of operator (&) before it.
     * If one wants to, this can be specified explicitly.
     **/

    // Add the options to the options map
    op_map["1"] = Option("ALL", output_records_std);
    op_map["2"] = Option("PASS + FAIL", output_records_passfail);

    // define an approprate prompt for the user to receive.
    string prompt = "How you would like to output the student records?";

    // recieve the option inputted by the user, and then return it.
    return input_option(op_map, prompt);

}

/**
 * Processes the user's option for how to output the student grades, 
 * writting the results to an output file at a given (relative) directory.
 **/
bool do_option(const string& out_dir, const Option& opt, vector<Student_info>& students, string::size_type& maxlen)
{   

    // Get the (pointer to the) function to be used to write the grades.
    grades_funct f = opt.f;
    
    /**
     * =============
     * NULL POINTERS
     * =============
     * A pointer that is not assigned an address to 'point' to, 
     * and thus is not truly pointing to anything, is called a null pointer. 
     * 
     * If this is the case for the grade writting function pointer, then
     * it is assumed that the option does not exist. So give an appropriate
     * message and do nothing else, returning false to indicate a failure to
     * process the option.
     **/
    if(f == nullptr) {
        cout << "Option does not exist!";
        return false;
    }
            
    // Open the output file (or create a new one)
    ofstream out(out_dir);

    /**
     * Dereference the pointer to get the actual function it points to, then call it
     * to finally write the grades.
     **/
    (*f)(out, students.begin(), students.end(), maxlen);

    // Give message stating the (relative) directory of where the output was written to.
    cout << "Output written to \'" << out_dir << "\'." << endl;

    return true;
}

/**
 * ======================
 * COMMAND LINE ARGUMENTS
 * ======================
 * 1st argument: input file
 * 2nd argument: output file
 * Further arguments: extra input files
 **/
int main(int argc, char** argv)
{   
    // define vector for holding all the student records read.
    vector<Student_info> students;
    // used to hold the current record being read from the input
    Student_info record;
    
    // record the length of the longest name, for padding the output
    string::size_type maxlen = 0;

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

    // if no records were entered (successfully), only give an approprate message.
    if (students.empty()) {
        cout << "No records entered." << endl;
    }

    // otherwise, output the student records finally.
    else {
        // first alphabetize the student records
        sort(students.begin(), students.end(), compare);

        // get the option that the user selects.
        Option option = choose_option();

        // process the option, getting a flag determining whether it was done successfully.
        bool option_done = do_option(output_dir, option, students, maxlen);

        // If it failed to be process for some reason, take this into account
        if (!option_done)
            ++fail_count;
    }

    // return the number of failed processes, to help determine how successful the program was.
    return fail_count;
}
