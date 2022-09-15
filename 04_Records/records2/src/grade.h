#ifndef GUARD_grade_h
#define GUARD_grade_h

// grade.h
#include <vector>
#include "Student_info.h"

double grade(int, int, double);
double grade(int, int, const std::vector<int>&);
double grade(const Student_info&);

#endif