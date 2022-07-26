// Represents a concordance
#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "split.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::max;
using std::sort;
using std::string;
using std::vector;


// a data structure that holds a vector of words and an index pointing to a word to be focused on.
struct Rotation
{
    vector<string> words;
    vector<string>::size_type pivot;
};


// the ordering of Rotation objects is represented by the alphabetical order of focused words
bool compare(Rotation r1, Rotation r2)
{
    return r1.words[r1.pivot] < r2.words[r2.pivot];
}


// Calculates the width of the sentence formed by a vector of words, only considering those bound between the two given iterators.
string::size_type width(const vector<string>::const_iterator& begin, const vector<string>::const_iterator& end) 
{
    // no width if the iterators are the same
    if(begin == end)
        return 0;

    // calculate the width of the section of the phrase bounded by the iterators, including also blank space between words.
    string::size_type w = 0;
    for(vector<string>::const_iterator it = begin; it != end; ++it) {

        w += ((*it).size() + 1);
    }
    return w - 1;
}


/**
 * Calculates the width of the sentence formed by the vector of words, for padding the output later.
 * The width is defined in the following way. Consider a phrase of the form
 *                  word_1 word_2 word_3 ... word_N
 * Then
 * width = size(word_1) + ... + size(word_{N-1}) + blanks between word_1 and word_{N-1}
 **/
string::size_type width(const vector<string>& v) 
{   
    return width(v.begin(), v.end() - 1);

    // if(v.size() <= 1)
    //     return 0;

    // string::size_type w = v.size() - 2;

    // for(vector<string>::const_iterator it = v.begin(); it != v.end() - 1; ++it) {

    //     w += (*it).size();
    // }

    // return w;
}


int main()
{
    // will temporarily hold a phrase as it is inputted.
    string x;
    
    // will store all the phrases that were inputted.
    vector<string> phrases;

    // store Rotation objects corresponding to each word of each phrase
    vector<Rotation> rotations;

    string::size_type maxlen = 0;

    // prompt the user to input phrases
    cout << "Enter a set of phrases to form a concordance: " << endl;

    // read each line of input and store it in a vector (until EOF recieved)
    while (getline(cin, x)) {
        phrases.push_back(x);
    }

    // iterate over each phrase received
    for(vector<string>::const_iterator it = phrases.begin(); it != phrases.end(); ++it) {
        
        // split the phrase into its words
        vector<string> words = split(*it);

        // record the maximum width of the word for the sake of padding when we start outputting results
        maxlen = max(maxlen, width(words));

        // create a Rotation data structure for each word and add it to the full collection.
        for(vector<string>::size_type j = 0 ; j != words.size(); ++j){
            Rotation r;
            r.words = words;
            r.pivot = j;
            rotations.push_back(r);
        }
    }

    // sort the rotations according to the alphabetical order of their associated words.
    sort(rotations.begin(), rotations.end(), compare);

    cout << endl;

    // output a concordance out of the inputted phrases
    for(vector<Rotation>::const_iterator iter = rotations.begin(); iter != rotations.end(); ++iter) {

        // "iter -> words" is equivalent to writting "(*iter).words".
        vector<string> words = iter->words;
        
        // output each word of the entire phrase up to the pivot word (exclusive) 
        for(vector<string>::size_type j = 0; j != iter->pivot; ++j) {
            cout << " " + words[j];    
        }
        // make sure to add a space even if the pivot is the first index.
        if(iter->pivot == 0){
            cout << " ";
        }

        // padding (and divider) between the words before the pivot, and the words after and including the pivot
        cout << string(maxlen + 1 - width(words.begin(), words.begin() + iter->pivot), ' ') << '|';

        // output the pivot and remaining words of the phrase.
        for(vector<string>::size_type j = iter->pivot; j != words.size(); ++j) {
         
            cout << words[j] << " ";
        }
        cout << endl;
    }
    return 0;
}