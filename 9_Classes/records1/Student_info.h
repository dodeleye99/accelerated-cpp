#ifndef GUARD_Student_info_h
#define GUARD_Student_info_h

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
    //  (member variables and member functions cannot share names)
    std::string n;  

    int midterm, final;
    std::vector<int> homework;

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

    /* ----- "Method" functions ------ */
    // calculate the student's (final) grade
    double grade() const;
    // interpret user's input to initialise the Student_info object
    std::istream& read(std::istream&);
    // check whether this record is "vaild" for use (i.e. whether there are any homework grades)
    bool valid() const {return !homework.empty();}
};

// (Note that this function is OUTSIDE the class)
// used to determine how two student records should be ordered
bool compare(const Student_info&, const Student_info&);

#endif