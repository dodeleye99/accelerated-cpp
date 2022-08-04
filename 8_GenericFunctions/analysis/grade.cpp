#include <stdexcept>
#include <vector>

#include "average.h"
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;
using std::vector;


// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(int midterm, int final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades and vector of homework grades.
double grade(int midterm, int final, const vector<int>& hw)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.size()== 0)
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, median<int>(hw.begin(), hw.end()));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

// compute a student's final grade, using the aveage value of the homework grades rather than the median.
double average_grade(int midterm, int final, const vector<int>& hw)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.size()== 0)
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, average<int>(hw.begin(), hw.end()));

}

double average_grade(const Student_info& s)
{
    return average_grade(s.midterm, s.final, s.homework); 
}

// predicate to determine whether a student failed
bool fgrade(const Student_info& s) 
{
    // We assume that a grade lower than 60 marks a fail.
    return grade(s) < 60;
}
