#ifndef GUARD_options_h
#define GUARD_options_h

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "Student_info.h"


// define type mnemonics
typedef std::vector<Student_info>::iterator v_iter;
typedef string::size_type str_sz;

// represents a pointer to a function with no return type, with parameter list of the types shown.
typedef void (*grades_funct) (std::ostream&, v_iter, v_iter, str_sz);

/**
 * Represents a selectable option for how the user wants to output the student grades.
 **/
struct Option {

    // represents the text used to briefly decribe the option.
    std::string label;
    // a pointer to the function representing the actual processor for outputting the grades.
    grades_funct f;

    // defaut constructor
    Option();
    // member initialisation contructor
    Option(std::string, grades_funct);
};

// A type representing a map of options, with keys representing text the user should enter to select them.
typedef std::map<std::string, Option> Option_map;

/**
 * Output sequence of student records bound by iterators [b, e) in the usual way,
 * line by line.
 **/
void output_records_std(std::ostream&, v_iter, v_iter, str_sz);

/**
 * Output sequence of student records bound by iterators [b, e),
 * Dividing output based on whether they passed or failed.
 **/
void output_records_passfail(std::ostream&, v_iter, v_iter, str_sz);

/**
 * Has the user input an option, out of a given range of them, for how to output the student grades.
 **/
Option input_option(const Option_map&, const string&);

#endif