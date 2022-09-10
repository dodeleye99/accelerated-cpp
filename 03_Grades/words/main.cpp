// this program takes a sequence of words inputted by the user and outputs the number of times each distinct word occurs.
#include <iostream>
#include <string>
#include <vector>

using std::cin;     using std::string;
using std::cout;    using std::vector;
using std::endl;


int main()
{
    // Prompt user to input a sequence of words
    cout << "Input any sequence of words, "
             "followed by end-of-file: ";

    // Use a variable to read over each word.
    string w;

    // Create a vector that will hold each distinct word.
    vector<string> words;
    /*
    Create a vector that will hold the number of times the word in the
    corresponding index of 'words' appears in the input.
    */
    vector<int> count;

    typedef vector<double>::size_type vec_sz;

    // invariant: - words contains all the unique words read so far.
    // - count contains the number of times each unique word read so far appears in input.
    while(cin >> w) {

        // Use a flag for determining whether the current word is new.
        bool distinct = true;

        // Use a variable to iterate over each word in the vector.
        vec_sz i = 0;

        // invariant: distinct is true iff none of the values read so far match w.
        while (i < words.size() && distinct) {
            // Set flag to false if match found. The loop will then end.
            if (w == words[i])
                distinct = false;
            
            // Otherwise, move on to the next index.
            else 
                ++i;
        }

        // If the flag is unchanged, then the word is new.
        if (distinct) {
            // Add the word to the 'word' vector.
            words.push_back(w);
            // Add 1 to the 'count' vector, indicating that it has appeared only once so far.    
            count.push_back(1);
        }
        // Otherwise, the word is not new, so increment the count of the word.
        else {
            ++count[i];
        }

    }

    // The size of the vector detetrmines the number of distinct words.
    vec_sz size = words.size();

    // First check whether no words were entered.
    if (size == 0) {
        cout << endl << "You must enter a sequence of words. "
                        "Please try again." << endl;
        // End the program, returning non-zero value to indicate failure.
        return 1;
    }

    // Prepare to output message displaying the word counts.
    cout << "Number of times each distinct word appears: " << endl;

    // Loop through each word and corresponding count, and output them.
    for (vec_sz i = 0; i < size; ++i) {
        cout << words[i] << ": " << count[i] << endl;
    }
    
    return 0;
}