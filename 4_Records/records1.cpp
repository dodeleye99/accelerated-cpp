#include <algorithm>    // defines std::sort and std::max
#include <iomanip>      // defines std::setpecision and other manipulators
#include <ios>          // defines std::streamsize
#include <iostream>     // defines std::cin, std::cout, std::endl and std::istream
#include <stdexcept>    // defines std::domain_error
#include <string>       // defines std::string
#include <vector>       // defines std::vector

using std::cin;             using std::setprecision;          
using std::cout;            using std::sort;
using std::domain_error;    using std::streamsize;
using std::endl;            using std::string; 
using std::istream;         using std::vector; 
using std::max;

// Data structure representing the user input for the name and grades of a single student.
struct Student_info {
    string name;
    int midterm, final;
    vector<int> homework;
}; // notice the semicolon - it's required

// read howework grades from an input stream into a vector<double>
istream& read_hw(istream& in, vector<int>& hw) 
{
    // Only proceed to read if there is no problem with the input stream already.
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

// read and store midterm and final grades, and homework grades of a single student. 
istream& read(istream& is, Student_info& s) 
{
    // read and store the student's name and midterm and final grades.
    is >> s.name >> s.midterm >> s.final;

    // read and store all the student's homework grades
    read_hw(is, s.homework);

    // (We have the function return the stream instead of a Student_info data structure in order to determine
    //  whether the read was successful or not)
    return is;
}

// compute the median of a vector<double>
// note that calling this function copies the entire argument vector (i.e. call by value), thus the sort() function causes no side effects
double median(vector<int> vec)
{
    // use the name 'vec_sz' as a synonym for vector<double>::size_type, so that it is easier to read and write.
    typedef vector<int>::size_type vec_sz;

    // get the number of elements in the vector
    vec_sz size = vec.size();

    // if the size is zero, then no median exists.
    if (size == 0) {
        // throw an exception of the appropriate type
        throw domain_error("median of an empty vector");
    }

    // sort the elements of the vector, from the first to the last, in monotonic increasing order. (i.e. non-decreasing)
    sort(vec.begin(), vec.end());

    // Calculate the midpoint (rounded down to nearest integer) of the vector
    vec_sz mid = size/2;

    // calculate the median: 
    // - if the size is even, then the median is equal to the sum of the element in the mid position and the previous one.
    // - otherwise (if size is odd), the median is equal to the element in the mid position.
    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2.0 : vec[mid];

    // alternatively, we could have written:
    // if (size % 2 == 0)
    //     return (vec[mid] + vec[mid-1])/2;
    // else
    //     return  vec[mid];
}

// compute the mean of a vector<double>
double mean(vector<int> vec){

    typedef vector<int>::size_type vec_sz;

    vec_sz size = vec.size();

    if (size == 0) {
        throw domain_error("mean of an empty vector");
    }

    int sum = 0;

    for(vec_sz i = 0; i < size; ++i){
        sum += vec[i];
    }

    return sum / (double)size;
}

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
    
    // for an alternative grading scheme, replace 'median' with 'mean'
    return grade(midterm, final, median(hw));
}

double grade(const Student_info& s)
{
    return grade(s.midterm, s.final, s.homework);
}

// compare two students by their name
bool compare(const Student_info& x, const Student_info& y)
{
    return x.name < y.name;
}

int main()
{
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    cout << "Please enter the records of each student (name, midterm and final exam grades, homework grades): " << endl;

    // read and store all records, and find the length of the longest name
    while (read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphabetize the records
    sort(students.begin(), students.end(), compare);

    cout << "\nFinal Grades: " << endl;

    for (vector<Student_info>::size_type i = 0;
         i != students.size(); ++i) {

        // write the name, padded on the right to maxlen + 1 characters. 
        cout << students[i].name
             << string(maxlen + 1 - students[i].name.size(), ' ');

    // compute and write the grade
        try {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec);
        } catch (domain_error e) {
            cout << e.what();
        }
        cout << endl;
    }

    return 0;
}
