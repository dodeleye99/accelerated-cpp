// A program that writes student records to separate files. 
#include <algorithm>
using std::back_inserter;
using std::transform;
using std::find;
using std::find_if;
using std::sort;
using std::stable_sort;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ofstream;

#include "Str.h"
#include "Student_info.h"
#include "Vec.h"

/**
 * Reads from an input stream student grade data and adds it to the end of a
 * Vec. Duplicate student names will not be added.
 **/
void read_input(istream& in, Vec<Student_info>& students)
{   
    // used to hold the current record being read from the input
    Student_info record;

    // used to hold all the names read so far.
    Vec<Str> read_names;

    while (record.read(in)) {

        // to prevent duplicates, we only add records that have a unique name - not matching those read so far.
        if(find(read_names.begin(), read_names.end(), record.name()) == read_names.end()) {
            students.push_back(record);
            read_names.push_back(record.name());
        }
        // if the student's name already exists, the record read will be discarded.
        else {
            cout << "Duplicate name (" << record.name() << ") will be ignored." << endl;
        }
    }
}
/**
 *  Writes each student record to a separate file.
 *  
 *  Example of a student record:
 *  =========================
 *  Name        : John         // Name of the student
 *  Reg. Pos.   : 10 / 20      // Position in the register, alphebetical order
 *  Grade       : 85           // Final grade (N/A if record invalid)
 *  Letter      : B            // Letter grade (N/A if record invalid)
 *  Class Rank  : 5 / 20       // Rank of student's grade out of entire class.
 *  =========================
 * (Stored in record-John.txt)
 **/
void create_record_files(Vec<Student_info>& students)
{   
    // Type mnemonics
    typedef Vec<Student_info>::const_iterator c_iter;
    typedef Vec<Student_info>::size_type size_type;

    // Top and bottom border lines
    const Str border_line(25, '=');

    // Define labels
    const Str l_name       = "Name        : ";
    const Str l_reg_pos    = "Reg Pos     : ";
    const Str l_grade      = "Grade       : ";
    const Str l_letter     = "Letter      : ";
    const Str l_class_rank = "Class Rank  : ";

    // Get total number of student records
    const size_type total = students.size();

    // Sort student records by the order of their names, in lexigraphical order
    sort(students.begin(), students.end(), compare);

    // Add the names to a Vec.
    Vec<Str> names;
    for(c_iter it = students.begin(); it != students.end(); ++it) {
        names.push_back(it->name());
    }

    // Sort student records by the order of their grades, largest to smallest.
    sort(students.begin(), students.end(), compare_grade);

    // The rank of the student out of the entire class(es)
    int class_rank = 1;

    // Iterate over the student records, writting each to an individual file.
    for(c_iter it = students.begin(); it != students.end(); ++it) {

        // Get the student's name
        const Str name = it->name();

        // Find first occurance of the name in the Vec.
        Vec<Str>::const_iterator name_it = find(names.begin(), names.end(), name);

        // Get the position (starting with 1) of the name, representing register order in the class(es)
        const int reg_pos = (name_it - names.begin()) + 1;
        
        // Create an output file to write the record to.
        ofstream out(("record-" + name + ".txt").c_str());

        // ----- Write the record to the output file ------

        // Write a top border line.
        out << border_line << endl;
        // Output the name and the student's position in the register.
        out << l_name << name << endl;  
        out << l_reg_pos << reg_pos << " / " << total << endl;  

        // Write data relating to the student grade if it is valid
        if(it->valid()) {
            out << l_grade << it->grade() << endl;
            out << l_letter << it->letter_grade() << endl;
            out << l_class_rank << class_rank << " / " << total << endl;
        }
        // Otherwise write "N/A" at the points where the data would have been
        else {
            out << l_grade << "N/A" << endl;
            out << l_letter << "N/A" << endl;
            out << l_class_rank << "N/A" << endl;
        }        
        // Finally write a bottom border line.
        out << border_line << endl;

        ++class_rank;
    }
}

int main(int argc, char** argv)
{   
    // define Vec for holding all the student records read.
    Vec<Student_info> students;

    // represents the number of files that could be opened
    int success_count = 0;
    // represents the number of files that could not be opened
    int fail_count = 0;

    // Determines whether no input arguments were entered, which indicates
    // that the user will enter the data directly from standard input.
    bool manual_mode = (argc <= 1);

    /** 
     * Read through every command-line argument, 
     * which represent the input files to read student records from 
     * (except the first, which is the name of the exectable file).
     **/
    for(size_t i = 1; i != argc; ++i) {
        // Open the output file (or create a new one)
        ifstream in_file(argv[i]);
        // If it was successfully opened, read it.
        if(in_file) {
            read_input(in_file, students);
            ++success_count;
        }
        // If not, give an appropriate message.
        else {
            cout << "Could not open \'" << argv[i] << "\'." << endl;
            ++fail_count;
        }
    }

    // If no files were entered, have the data entered the usual way
    // from the standard input stream (i.e. "manual mode").
    if(manual_mode) {
        // prompt the user to input the records directly
        cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades) "
                "directly, followed by end-of-file.\n"
                "(Please ensure that every name is unique - duplicates will be ignored.)\n" << endl;
        // read and store all records, and seek the length of the longest name
        read_input(cin, students);
    }

    // if in "input file mode", but the files entered could not be opened, 
    // give an appropriate message and end the program.
    else if (success_count == 0) {
        cout << "None of the input files could be opened.\n" << endl;
        return fail_count;
    }

    // if no records were entered (successfully), only give an approprate message.
    if (students.empty()) {
        cout << "No records entered." << endl;
    }

    // otherwise, write the student record files finally.
    else {
        create_record_files(students);
    }

    // return the number of failed processes, to help determine how successful the program was.
    return fail_count;
}