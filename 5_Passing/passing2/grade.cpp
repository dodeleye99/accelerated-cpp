#include <list>
#include <stdexcept>
#include <vector>

#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;
using std::list;
using std::vector;

// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(int midterm, int final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument (i.e. it is called by reference), because median does so for us anyway.
double grade(int midterm, int final, const vector<int>& hw)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.size()== 0)
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

// predicate to determine whether a student failed
bool fgrade(const Student_info& s) 
{   
    // We assume that a grade lower than 60 marks a fail.
    return grade(s) < 60;
}

// Separate passing and failing student records.
// (final version: based on v4, but also considers students with insufficient grades.)
list<Student_info> extract_fails(list<Student_info>& students)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();

    // invariant: elements [0, i) of 'students' represent passing grades.
    while(iter != students.end()) {

        try{
            if(fgrade(*iter)) {
                fail.push_back(*iter);
                iter = students.erase(iter);
            } 
            else
                ++iter;
        } 
        // If there is a domain error (due to insufficient grades) automaically mark it as a fail.
        catch (domain_error) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        }
    }
    return fail;
}

// === Development of the extract_fails() function ===

// v1: insert into two new vectors, separating passing and failing students.
vector<Student_info> extract_fails1(vector<Student_info>& students) 
{
    vector<Student_info> pass, fail;

    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i)
        if (fgrade(students[i]))
            fail.push_back(students[i]);
        else
            pass.push_back(students[i]);
        
    students = pass;
    return fail;

}

// v2: use only one new vector for failing students, and only keep the passing students in the current one
vector<Student_info> extract_fails2(vector<Student_info>& students) 
{
    vector<Student_info> fail;
    vector<Student_info>::size_type i = 0;

    // invariant: elements [0, i) of 'students' represent passing grades.
    while(i != students.size()) {
        if(fgrade(students[i])) {
            fail.push_back(students[i]);
            students.erase(students.begin() + i);
        }
        else
            ++i;  
    }
    return fail;
    
}

// v3: similar to v2, but using iterators instead.
vector<Student_info> extract_fails3(vector<Student_info>& students)
{
    vector<Student_info> fail;
    vector<Student_info>::iterator iter = students.begin();

    // invariant: elements [0, i) of 'students' represent passing grades.
    while(iter != students.end()) {
        if(fgrade(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else
            ++iter;  
    }
    return fail;
}

// v4: similar to v3, but using lists instead of vectors.
list<Student_info> extract_fails4(list<Student_info>& students)
{
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();

    // invariant: elements [0, i) of 'students' represent passing grades.
    while(iter != students.end()) {
        if(fgrade(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else
            ++iter;  
    }
    return fail;
}
/**
 * ------------------------------------------------
 * Why is lists prefered over vectors in this case?
 * ------------------------------------------------
 * The list data structure functions like a linked list (stores elements at non-contiguous memory locations), 
 *  giving it constant time to add and delete elements regardless of its size.
 * However, it lacks random access time to its elements, having to iterate from the first element of the list to get to the nth.
 * (Node 1)-------(Node 2)------(Node 3)
 * 
 * The vector data structure functions like a non-fixed size array (contiguous memory), giving it constant access time to any of its elements.
 * However, adding and deleting to a vector anywhere other than the end is slower than a list, since every element will have to be
 *  shifted accordingly. 
 * Iterators may also become invalidated as a consequence, due to the element it originally points to possibly being moved.
 * | 1 | 2 | 3 |
 * ---------
 * Summary:
 * ---------
 * Vectors (implements array):
 *  + Random Access (O(1))
 *  - O(n) add and delete unless it is a push_back()
 *  - Iterators may become invalidated after an add or delete due to elements being moved.
 * 
 * List (implements linked list):
 *  + O(1) add and delete
 *  - Non-random access (O(n))
 * 
 * Since extract_fails does not access its elements randomly but rather sequentially, and it will possibly delete elements from the
 * students container, then the lists data structure is the best choice in this case. 
 **/