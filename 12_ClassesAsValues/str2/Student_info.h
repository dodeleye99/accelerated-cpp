#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <algorithm>
#include <iostream>

#include "Str.h"


// class for representing student records
class Student_info {
    /**
     * Note that class members are private by default,
     * i.e. assume there is a 'hidden' "private:" declaration here
     * (this is what makes the defining classes with 'class' keyword different from using the 'struct' keyword)
     **/
    
    // ----------------------------------- Data elements ----------------------------------------

    // Holds the student's name. Called "n" since "name" is already used for the name() function
    //(member variables and member functions cannot share names)
    Str n;  

    // holds the final calculated grade for the student
    double final_grade;

    // holds whether the record is valid (will only be so if student did their homework)
    bool v;

// (use the public keyword to make the members under it freely accessible from outside the class)
public:
    // ----------------------------------- Constructors --------------------------------------

    // default constructor (no arguments)
    Student_info();
    // initialise directly from user input                
    Student_info(std::istream&);

    // ----------------------------------- (Public) member functions ------------------------
    // (The const keyword is used to guarantee that no data members are changed by the grade() function.)

    // ------ "Getter" functions ------
    // get student's name                 
    Str name() const {return n;}
    // check whether this record is "vaild" for use
    bool valid() const {return v;}

    // ----- "Method" functions ------
    // get student's (final) grade (will be slightly more than a simple "getter" function)
    double grade() const;
    // calculates the letter grade of the student based on their final grade
    Str letter_grade() const;
    // interpret user's input to initialise the Student_info object
    std::istream& read(std::istream&);

    // convert to a double using the student's final grade
    operator double() { return final_grade; };
    // convert to a bool by the validity of the student's record.
    operator bool() { return valid(); };
};

// --- (Note these this functions are OUTSIDE the class) ---

// used to determine how two student records should be ordered
bool compare(const Student_info&, const Student_info&);

// an alternative comparison scheme, using the value of their grades to determine the order (largest to smallest).
bool compare_grade(const Student_info&, const Student_info&);

// used to determine whether a student's grade indicates a fail.
bool fgrade(const Student_info&);

/**
 * Takes a sequence of student records bounded by forward iterators [b, e) 
 * and rearranges it so that the records with "fail" grades are at the front 
 * followed by all the "pass" records (thus the original sequence may be modified as a result).
 * 
 * It ensures thst the relative ordering of the records in each partition is preserved.
 * 
 * Outputs an iterator pointing to the first element of the second-half (passing students).
 **/
template<class Fwd>
Fwd extract_fails(Fwd b, Fwd e)
{
    return stable_partition(b, e, fgrade);
}

#endif