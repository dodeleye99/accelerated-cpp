#include <iostream>
using std::istream;

#include <stdexcept>
using std::domain_error;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "average.h"
#include "median.h"
#include "Student_info.h"

typedef vector<int>::iterator iter;

/* ================= "Helper" functions used to define the member functions of Student_info =================== */

// read howework grades from an input stream into a vector<int>
istream& read_hw(istream& in, vector<int>& hw) 
{
    // Only proceed to read if there is is a problem with the input stream already.
    if (in) {

        // get rid of previous contents
        hw.clear();

        // read homework grades
        int x;
        // invariant: hw contains all the homework grades read so far
        while (in >> x)
            // append x at the end of the hw vector
            hw.push_back(x);

        // clear the stream so that input will work for the next student.
        in.clear();
    }

    // (We have the function return the stream instead of a vector of the grades in order to determine
    //  whether the read was successful or not)
    return in;
}

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(int midterm, int final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

/**
 * Compute a student's overall grade from midterm and final exam grades and vector of homework grades.
 * The "hw grading scheme" method can also be specified. By default it used median, 
 * acting as the "standard grading scheme."
 * For the "average grading scheme", one would need to specify instead the average() function instead.
 **/
double grade(int midterm, int final, vector<int> hw, 
                double hw_grade_method(iter, iter) = median<int, iter>)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.empty())
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, hw_grade_method(hw.begin(), hw.end()));

}

/* =============================== Definitions of Student_info member functions ================================================*/

/* ----------------------------------- Constructors ---------------------------- */
Student_info::Student_info(): final_grade(0), v(false){ }
Student_info::Student_info(istream& is) { read(is); }


/* ------------------------- (Public) member functions --------------------------- */
double Student_info::grade() const
{   
    // throw an error if the student record is invalid (due to no homework)
    if (!valid())
        throw domain_error("student has done no homework");
    return final_grade;
}

// reads and stores midterm and final grades, and homework grades of a single student. 
istream& Student_info::read(istream& in)
{   
    // initialise variables used to calculate the final grade (of which we are only insterested in recording)
    int midterm, final;
    vector<int> homework;

    // read and store the student's name and midterm and final grades.
    in >> n >> midterm >> final;
    // read and store all the student's homework grades
    read_hw(in, homework);

    // determine validity of the record by checking whether homework grades were entered.
    v = !homework.empty();

    // calculate the final grade if the record is valid.
    if(v) 
    {
        /**
         * Note the scope :: operator here, used to show that we want to call the grade() function in the scope of
         * this source file, and NOT the scope of the Student_info class (its member function of the same name)
         **/
        final_grade = ::grade(midterm, final, homework);
    }
        
    // (We have the function return the stream instead of a Student_info data structure in order to determine
    //  whether the read was successful or not)
    return in;
}

bool compare(const Student_info& x, const Student_info& y)
{   
    // we compare two students by their name
    return x.name() < y.name();
}

bool fgrade(const Student_info& s) 
{   
    /**
     * We assume that gradeS lower than 60 marks a fail. We also assume non-valid 
     * records (no h/w) are an automatic fail.
     * 
     * (The way || (or) works is that if the left-hand of the expression is true, 
     *  then it produces true for the whole expression without needing to read the right-hand side.
     * It only proceess to the right-hand side if the left-hand side is false.
     * Thus, checking first whether it is valid safely allows us to assume it truly is when checking
     *  the grade, avoiding a domain_error being produced).
     **/
    return !s.valid() || s.grade() < 60;
}