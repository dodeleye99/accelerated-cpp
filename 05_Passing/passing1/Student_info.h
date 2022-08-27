#ifndef GUARD_Student_info
#define GUARD_Student_info

// Student_info.h header file
#include <iostream>
#include <string>
#include <vector>

struct Student_info {
    std::string name;
    int midterm, final;
    std::vector<int> homework;
}; // notice the semicolon - it's required

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<int>&);

#endif