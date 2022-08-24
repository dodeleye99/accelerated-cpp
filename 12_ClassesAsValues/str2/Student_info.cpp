#include <iostream>
using std::istream;

#include <stdexcept>
using std::domain_error;

#include "average.h"
#include "median.h"
#include "Str.h"
#include "Vec.h"
#include "Student_info.h"


typedef Vec<int>::iterator iter;

// ================= "Helper" functions used to define the member functions of Student_info ===================

// read howework grades from an input stream into a Vec<int>
istream& read_hw(istream& in, Vec<int>& hw) 
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
double grade(int midterm, int final, Vec<int> hw, 
                double hw_grade_method(iter, iter) = median<int, iter>)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.empty())
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, hw_grade_method(hw.begin(), hw.end()));

}

// takes a student's grade as input and outputs the letter grade 'tier' it falls into.
Str letter_grade(double grade)
{
    /**
     * ==========================
     * Letter grading boundaries:
     * ==========================
     *  97 - 100:    A+
     *  94 -  96:    A
     *  90 -  93:    A-     
     *  87 -  89:    B+
     *  84 -  86:    B
     *  80 -  83:    B-
     *  77 -  79:    C+
     *  74 -  76:    C
     *  70 -  73:    C-
     *  60 -  69:    D
     *   0 -  69     F
     **/

    // range posts for numeric grades
    static const double numbers[] = {
        97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0
    };
    // names for the letter grades
    static const char* const letters[] = {
        "A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F" 
    };
    /**
     * ===================================================
     *          THE TRUTH BEHIND STRING LITERALS
     * ===================================================
     * A string literal is a mnemonic for an array of characters
     * E.g. "hello" is actually the array 
     *              {'H', 'e', 'l', 'l', 'o', '\0'} 
     * (where '\0' is a null pointer added automatically indicate the end of the char array)
     * 
     * Whenever an array is used as a value, the pointer to the first element of an array is used instead
     * Thus the char* type also represents an array of chars.
     * And so letters[] is an array of character pointers each poining to an array
     * ===================================================
     *          THE TWO USES OF THE const KEYWORD
     * ===================================================
     * const char* const letters[]: An array of constant pointers to const char types (arrays).
     * 
     * - The fist const (const char*) means that each pointer is to a constant char. That is, their
     *   values are READ-ONLY (as with input iterators) so that it can be dereferenced ONLY 
     *   for reading the value, NOT for reassigning it. 
     *   (e.g. "A+" can't be changed to "S", and even "+" to "*" is illegal)
     * 
     * - The second const (char* const) means that each pointer themselves cannot be modified
     *   (e.g. by ++). Thus it are is "locked" at the address it points to. 
     * 
     * Therefore, thinking of it as an array of strings, the elements CANNOT be replaced with
     * other strings (because of the first const), and a pointer to any of the string cannot be given
     * another address, and so it cannot point to another element (because of the second const).
     * 
     * A reference to letters (used as a pointer) will ALWAYS be a pointer to its first element, 
     * which is read-only along with the rest of the elements of the array.
     **/
    
    /**
     * ================ FINDING THE CAPACITY OF AN ARRAY =====================================
     * There is no simple function for calculating the size of a built-in array in C++.
     * One has to do basic math with the sizeof() function:
     * 
     * sizeof(obj): returns the number of bytes occupied by an object.
     * 
     * By calculating the number of bytes occupied by an entire array, and dividing it
     * by the number of bytes used by any element of the array (each will have the same size),
     * the size can effectively be found.
     * ========================================================================================
     * 
     * Thus we can compute the number of grades given the size of the array 
     * and the size of a single element (such as the first)
     **/
    static const size_t ngrades = sizeof(numbers) / sizeof(*numbers);

    // given a numeric grade, find and return the associated letter grade
    for (size_t i = 0; i < ngrades; ++i) {
        if (grade >= numbers[i])
            return letters[i];
    }

    /**
     * If the grade is invalid (<0) then return "???" to indicate this.
     * (The escape sequence \?, which still gives ?, is used since ?? is a trigraph - that is,
     * it is treated by C++ as a single character meaning something different)
     **/
    return "?\?\?";
}

// =============================== Definitions of Student_info member functions ================================================

// ----------------------------------- Constructors ----------------------------
Student_info::Student_info(): final_grade(0), v(false){ }
Student_info::Student_info(istream& is) { read(is); }

// ------------------------- (Public) member functions ---------------------------
double Student_info::grade() const
{   
    // throw an error if the student record is invalid (due to no homework)
    if (!valid())
        throw domain_error("student has done no homework");
    return final_grade;
}

Str Student_info::letter_grade() const
{   
    // throw an error if the student record is invalid (due to no homework)
    if (!valid())
        throw domain_error("student has done no homework");
    return ::letter_grade(final_grade);
}

// reads and stores midterm and final grades, and homework grades of a single student. 
istream& Student_info::read(istream& in)
{   
    // initialise variables used to calculate the final grade (of which we are only insterested in recording)
    int midterm, final;
    Vec<int> homework;

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

// ------------------------- Misc. ---------------------------

bool compare(const Student_info& x, const Student_info& y)
{   
    // we compare two students by their name
    return x.name() < y.name();
}

bool compare_grade(const Student_info& x, const Student_info& y)
{   
    // TEST: Is the grade of x greater than the grade of y?

    // If x is invalid, then the grade of y is treated as greater (or equal if also invalid) by default.
    if (!x.valid())
        return false;
    // If x is valid, but y is invalid, then the grade of x is treated as the greater value by default.
    if(!y.valid())
        return true;

    // If both valid, then we compare two students by their grade
    return x.grade() > y.grade();
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