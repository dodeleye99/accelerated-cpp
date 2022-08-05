#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// class for representing student records
class Student_info {
    /**
     * Note that class members are private by default,
     * i.e. assume there is a 'hidden' "private:" declaration here
     * (this is what makes the defining classes with 'class' keyword different from using the 'struct' keyword)
     **/
    
    /* ----------------------------------- Data elements ---------------------------------------- */

    // Holds the student's name. Called "n" since "name" is already used for the name() function
    //(member variables and member functions cannot share names)
    std::string n;  

    // holds the final calculated grade for the student
    double final_grade;

    // holds whether the record is valid (will only be so if student did their homework)
    bool v;

// (use the public keyword to make the members under it freely accessible from outside the class)
public:
    /* ----------------------------------- Constructors -------------------------------------- */

    // default constructor (no arguments)
    Student_info();
    // initialise directly from user input                
    Student_info(std::istream&);

    /* ----------------------------------- (Public) member functions ------------------------ */
    // (The const keyword is used to guarantee that no data members are changed by the grade() function.)

    /* ------ "Getter" functions ------ */
    // get student's name                  
    std::string name() const {return n;}
    // check whether this record is "vaild" for use
    bool valid() const {return v;}

    /* ----- "Method" functions ------ */
    // get student's (final) grade (will be slightly more than a simple "getter" function)
    double grade() const;
    // interpret user's input to initialise the Student_info object
    std::istream& read(std::istream&);
};

// (Note that this function is OUTSIDE the class)
// used to determine how two student records should be ordered
bool compare(const Student_info&, const Student_info&);

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