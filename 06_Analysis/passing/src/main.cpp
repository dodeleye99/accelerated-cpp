#include <algorithm>    // defines std::sort, std::max, std::remove_copy_if, std::remove_if, std::stable_partition
#include <iomanip>      // defines std::setprecision and other manipulators
#include <ios>          // defines std::streamsize
#include <iostream>     // defines std::cin, std::cout, std::endl and std::istream
#include <stdexcept>    // defines std::domain_error
#include <string>       // defines std::string
#include <vector>       // defines std::vector

#include "grade.h"
#include "Student_info.h"   // defines Student_info structure, and compare(), read(), read_hw() functions


using std::cin;             using std::setprecision;
using std::cout;            using std::sort;
using std::domain_error;    using std::stable_partition;
using std::endl;            using std::streamsize;
using std::max;             using std::string; 
using std::remove_copy_if;  using std::vector;
using std::remove_if;


// write names and grades from a list of students
void output_grades(const vector<Student_info>& students, const string::size_type pad_factor)
{
    for (vector<Student_info>::const_iterator iter = students.begin(); iter != students.end(); ++iter)
    {
        // write the name, padded on the right to maxlen + 1 characters. 
        cout << (*iter).name
             << string(pad_factor + 1 - (*iter).name.size(), ' ');

        // compute and write the grade
        try {
            double final_grade = grade(*iter);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }
}

// we need a single predicate to work with the "remove_if" functions and stable_partition()
bool pgrade(const Student_info& s)
{   
    try {
        return !fgrade(s);
    } 
    // if there is a domain error (due to insufficient grades) automaically mark student grade as a fail.
    catch (domain_error) {
        return false;
    }
}

/**
 * A two-pass algoritm that extracts from a collection of student records all the students with failing grades.
 * (Note that the original vector may be modified as a result)
 **/
vector<Student_info> extract_fails1(vector<Student_info>& students)
{
    // prepare a vector that will hold all the students with failing grades.
    vector<Student_info> fail;

    // Without modifying the original vector, disregard all students with passing grades, 
    //  leaving only the ones with failed grades to be considered, adding them to the fail vector.
    remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);

    /**
     * Now disregard all students with fail grades, leaving only the ones with passing grades to be considered.
     * then delete those failing students from the 'students' vector.
     * (Note: remove_if() modifies the vector, putting the element to keep at the front, 
     *  returning an iterator pointing to one past the last element to keep)
     **/

    /**
     * -----------------------------------------------------------------------------
     * Steps taken to erase students with failing grades from the 'students' vector:
     * -----------------------------------------------------------------------------
     * 1) Disregard all the students with failing grades, considering only those with passing grades.
     * 2) Write the students with passing grades into the students vector, starting from the front of the vector.
     * (This will overwrite the student records originally at these positions)
     * 3) Retrieve an iterator pointing to one past the last element that was written to (remove_if() will return it)
     * 4) Erase the "garbage" elements left in the students array, which will be in the range starting from this iterator
     * to the end of the vector.
     **/
    students.erase(remove_if(students.begin(), students.end(), fgrade), students.end());

    return fail;
}

/**
 * A single-pass algorithm that extracts from a collection of student records all the students with failing grades.
 * (Note that the original vector may be modified as a result)
 * This version checks the student's grades only once (single-pass), while the older version needs to check twice (two-pass))
 * Thus it improves from extract_fails1(), taking less the time to carry out the extraction.
 **/
vector<Student_info> extract_fails2(vector<Student_info>& students)
{
    /**
     * Use stable_partition() to rearrange the 'students' vector in such a way that it consist of two halves:
     * the passing students first, followed by the failing students.
     * Retrieve an iterator pointing to the first element of the second-half (failing students).
     **/
    vector<Student_info>::iterator iter = stable_partition(students.begin(), students.end(), pgrade);
    
    // Create and initialise a new vector holding all the elements from the 'failing' half
    vector<Student_info> fail(iter, students.end());

    // Erase from the 'students' vector all the elements of the 'failing' half, leaving behind only passing students.
    students.erase(iter, students.end());

    return fail;
}

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades), "
            "followed by end-of-file: " << endl;

    // read and store all records, and find the length of the longest name
    // Invariant: 'students' contains all the student records read so far
    //            'maxlen' contains the length of the longest name in 'students'       
    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    
    // extract the failing students from the list of students
    // the students list will then only contain those who passed.
    vector<Student_info> fails = extract_fails2(students);

    // alphabetize the records
    sort(students.begin(), students.end(), compare);
    sort(fails.begin(), fails.end(), compare);
    
    // first output the names and grades of the students that passed
    cout << "\nStudents that passed: " << endl;
    output_grades(students, maxlen);

    // then output the names and grades of the students that failed
    cout << "\nStudents that failed: " << endl;
    output_grades(fails, maxlen);

    return 0;
}

/**
 * === ALGORITHMS ===
 * remove_copy_if(iter1, iter2, iter_out, f) - functions similarly to remove_copy, but uses a predicate to determine f
 * which values to disregard (f(*iter) == true).
 * -------------------
 * remove_if(iter1, iter2, f) - unlike remove_copy_if, it modifies the original container, extracting from it all the values that
 * pass a predicate (f(*iter) == true). What actually happens is that the remaining values are written from the front of the
 * container, and it returns an iterator poining to one past the last element to keep.
 * -------------------
 * stable_partition(iter1, iter2, f) - uses a predicate f to rearrange a container bound by iterators [iter1, iter2) into two halves.
 * The first half consist of values that pass the predicate, while the second half which follows consist of values that fail it.
 * Its 'stable' in that the relative order between the elements of each half is preserved as before.
 ***/