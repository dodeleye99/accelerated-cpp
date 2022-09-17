#include <iostream>     // defines cin, cout, endl, istream
#include <map>          // defines map
#include <stdexcept>    // defines logic_error
#include <string>       // defines getline, string
#include <vector>       // defines vector

#include "nrand.h"          // defines nrand
#include "split.h"          // defines split

using std::cin;             using std::logic_error;                
using std::cout;            using std::map;                 
using std::endl;            using std::string;           
using std::getline;         using std::vector;
using std::istream;   


// Represents a rule of the grammar under some category, 
//  made up of a combination of basic words and other rule-categories.
typedef vector<string> Rule;

// Represents the complete collection of rules found under a particular category.
typedef vector<Rule> Rule_collection;

// Represents a grammar, a well-defined collection of rules divided into a finite number of categories.
typedef map<string, Rule_collection> Grammar;


// read a grammar from a given input stream
Grammar read_grammar(istream& in)
{   
    // create a map to represent the grammar being read from the input
    Grammar ret;

    // define string for storing the current line read.
    string line;

    /**
     * Read each line of input one by one.
     * Each line represents a rule, made of two parts:
     *      rule-category: the FIRST word in the line identifying the category the rule falls under.
     *      rule-definition: the remaning words in the line defining the rule.
     * It will be of the form:
     * <rule-category>  rule-definition
     **/
    while (getline(in, line)) {

        // split the line of text into words
        vector<string> entry = split(line);

        if(!entry.empty()) {
            // using the rule category as the key, store the associated rule in the grammar
            // (assumed to be of form (with '<>' brackets): <name-of-category>) 
            ret[entry[0]].push_back(
                // the rule represented by the rest of the string is broken down into its individual words
                Rule(entry.begin() + 1, entry.end()) 
            );
        }
    }
    return ret;
}

// checks whether a string is surrounded by '<>' brackets, which represents a rule-category.
bool bracketed(const string& s)
{   
    /**
     * The way && (and) works is that if the left-hand of the expression is false, 
     *  then it produces false for the whole expression without needing to read the right-hand side.
     * Thus, checking first that it is non-empty safely allows us to assume it truly is in the right-hand side
     *  of the expression, avoiding a domain_error being produced.
     **/
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

/**
 * =================================================================================================
 * This is a recursive function for generating a random sentence from a given grammar.
 * =================================================================================================
 * GENERAL OVERVIEW OF RECURSION
 * -------------------------------------------------------------------------------------------------
 * Step 0: Call the function for the first time, inputting initial arguments.
 * Step 1: Specify immediate exit condition  
 * Step 2: Do necessary recursive call(s), using different or modified arguments when applicable.
 * Step 3: Immediately exit after the call(s).
 * =================================================================================================
 * PARAMETERS OF THE FUNCTION
 * -------------------------------------------------------------------------------------------------
 * g   : represents the grammar the sentence is being generated from.
 * word: represents the current word being read. 
 *       - if a rule-category, then a random rule under it
 *          is searched from the grammar, and recursion is done for "expanding" each word in 
 *          the chosen rule.
 *       - if not, then the word is added at the end of the ret vector.
 * ret : represents the sentence that will ultimately generated.
 * =================================================================================================
 **/
void gen_aux(const Grammar& g, const string& word, vector<string>& ret)
{
    // immediate exit condition: the current word is not a rule-category 
    if (!bracketed(word)) {
        // add the word to the vector of words
        ret.push_back(word);
    } else {
        // from the grammar locate the rule that corresponds to the word
        Grammar::const_iterator it = g.find(word);
        // a rule-category without any definitions counts as an empty rule.
        if (it == g.end())
            throw logic_error("empty rule");
        
        // fetch the set of possible rules under the category,
        const Rule_collection& c = it->second;

        // from which we can select one at random.
        const Rule& r = c[nrand(c.size())];

        // recursively expand the selected rule
        for (Rule::const_iterator i = r.begin(); i != r.end(); ++i)
            gen_aux(g, *i, ret);
    } 
}

// The "launcher" function for generating a generating random sentence from a given grammar.
// (the actual work is done by the gen_aux function)
vector<string> gen_sentence(const Grammar& g)
{
    vector<string> ret;
    // We use "<sentence>" as our "start symbol".
    gen_aux(g, "<sentence>", ret);
    return ret;
}

int main()
{   
    // the number of sentences to randomly generate from the grammar
    int n = 5;
    
    // prompt the user
    cout << "A grammar is an well-defined collection of rules used to define "
            "the words and syntax that a sentence should have." << endl;

    cout << "\nInput a grammar by entering lines of text that each represent a rule." << endl;
    cout << "Exactly " << n << " randomly generated sentences from the grammar will then be outputted." << endl;

    cout << "\nWrite each rule you would like to add to the grammar in the following form:" << endl;
    cout << "<rule-category> rule-definition" << endl;
    cout << "\n(Be sure to add AT LEAST ONE <sentence> rule to define the sentence(s) the grammar outputs):\n" << endl;

    // receive the grammar
    Grammar g = read_grammar(cin);

    // prepare to generate n random sentences.
    cout << endl;
    cout << "==============================" << endl;
    cout << "Generating " << n << " random sentences:" << endl;
    cout << "==============================" << endl;

    for(int i=0; i<5; ++i) 
    {
        // generate a sentence
        vector<string> sentence = gen_sentence(g);

        // write the first word, if any
        vector<string>::const_iterator it = sentence.begin();
        if(!sentence.empty()) {
            cout << *it;
            ++it;
        }

        // write the rest of the words, each preceded by a space
        while (it != sentence.end()) {
            cout << " " << *it;
            ++it;
        }

        cout << endl;

    }
    return 0;
}
// =====================================================================================
// (Category)         (Collection of rules to pick from)
// <rule-category> -> {[rule1], [rule2], [rule3], ... }
// =====================================================================================
// EXAMPLE OF GRAMMAR
// =====================================================================================
// <noun>           -> { [cat], [dog], [table], [fox], [fence] }
// <noun-phase>     -> { [<noun>], [<adjective>, <noun-phrase>] }
// <adjective>      -> { [large], [brown], [absurd], [lazy] }
// <verb>           -> { [jumps], [sits] }
// <adverb>         -> { [quickly], [slowly], [quietly], [loudly] }
// <location>       -> { [on, the, stairs], [under, the, sky], [wherever, it, wants] }
// <sentence>       -> { [the, <noun-phrase>, <verb>, <location>] }

// recursion: step 1, immediate exit. step 2, single recursive call, immediate exit on second call
