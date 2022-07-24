#include <algorithm>    // defines std::sort
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


// compute the median of a vector<double>
// note that calling this function copies the entire argument vector (i.e. call by value), thus the sort() function causes no side effects
double median(vector<double> vec)
{
    // use the name 'vec_sz' as a synonym for vector<double>::size_type, so that it is easier to read and write.
    typedef vector<double>::size_type vec_sz;

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
    return size % 2 == 0 ? (vec[mid] + vec[mid-1]) / 2 : vec[mid];

    // alternatively, we could have written:
    // if (size % 2 == 0)
    //     return (vec[mid] + vec[mid-1])/2;
    // else
    //     return  vec[mid];
}


// compute the mean of a vector<double>
double mean(vector<double> vec){

    typedef vector<double>::size_type vec_sz;

    vec_sz size = vec.size();

    if (size == 0) {
        throw domain_error("mean of an empty vector");
    }

    double sum = 0;

    for(vec_sz i = 0; i < size; ++i){
        sum += vec[i];
    }

    return sum / size;

}


// compute a student's overall grade from midterm and final exam grades and homework grade
double grade(double midterm, double final, double homework)
{
    return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}


// compute a student's overall grade from midterm and final exam grades
// and vector of homework grades.
// this function does not copy its argument (i.e. it is called by reference), because median does so for us anyway.
double grade(double midterm, double final, const vector<double>& hw)
{
    // if the size of the hw vector is zero, then there is no data that can be used to calculate the homework grades.
    if (hw.size()== 0)
        throw domain_error("student has done no homework");
    
    return grade(midterm, final, median(hw));

}


// read howework grades from an input stream into a vector<double>
istream& read_hw(istream& in, vector<double>& hw) 
{
    // Only proceed to read unless there is a problem with the input stream already.
    if (in) {

        // get rid of previous contents
        hw.clear();

        // read homework grades
        double x;
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


// This procedure is used to output the greeting.
void output_greeting(string greeting)
{
    // the number of blanks surrounding the greeting
    const int pad = 2;

    // total number of rows and columns write
    const int rows = pad * 2 + 3;
    const string::size_type cols = greeting.size() + pad * 2 + 2;

    // write a blank line to separate the output from the input
    cout << endl;

    // write 'rows' rows of output
    // invariant: we have written 'r' rows so far
    for(int r = 0; r != rows; r++) {

        string::size_type c = 0;

        // invariant: we have written c characters so far in the current row
        while (c != cols) {

            // is it time to write the greeting?
            if(r == pad + 1 && c == pad + 1) {
                cout << greeting;
                c += greeting.size();
            } else {
                // are we on the border?
                if (r == 0 || r == rows - 1 || c == 0 || c == cols - 1)
                    cout << "*";
                else
                    cout << " ";
                ++c;
            }
        } 

        cout << endl;
    }
}


int main()
{
    // ask for and read the student's name
    cout << "Please enter your first name: ";
    string name;
    cin >> name;

    const string greeting = "Hello, " + name + "!";
    output_greeting(greeting);

    // ask for and read the midterm and final grades
    cout << "Please enter your midterm and final exam grades: ";
    double midterm, final;
    cin >> midterm >> final;

    // ask for homework grades
    cout << "Enter all your homework grades, "
            "followed by end-of-file: "; // On macOS: new line, then ctrl-d

    // define vector that will hold all the homework grades
    vector<double> homework;

    // read the homework grades from the input stream
    read_hw(cin, homework);

    // compute and write the final grade, if possible
    try {
        // may replace 'median' with 'mean' for an alternative method of calculating final grade
        double final_grade = grade(midterm, final, median(homework));
        streamsize prec = cout.precision();
        cout << "Your final grade is " << setprecision(3)
         << final_grade << setprecision(prec) << endl;
    } catch (domain_error) {
        cout << endl << "You must enter your grades. "
            "Please try again." << endl;
        return 1;
    }

    return 0;
}

/**
 * 
 * - read_hw() involves reading an unknown number of grades, so we cannot determine beforehand where to stop reading.
 * We have to wait until end-of-file is reached, or if an invalid grade is entered. 
 * At these points, the read of homeworks should be successful, but these usually indicate error in the stream, and 
 * so it will not work the the next time a read is needed.
 * Therefore, to indicate that the read was indeed successful, we have to clear it with the clear() member function.
 * 
 **/
