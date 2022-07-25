#ifndef GUARD_grade_h
#define GUARD_grade_h

// grade.h
#include <vector>
#include <list>
#include "Student_info.h"

bool fgrade(const Student_info&);
double grade(int, int, double);
double grade(int, int, const std::vector<int>&);
double grade(const Student_info&);

#endif