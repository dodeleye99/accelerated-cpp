# Chapter 7: Maps

The student grading system is put on hold in this chapter to focus entirely on the **map** data structure in C++.
A map is a container that consisting of **key-value pairs**. It can be thought of as a vector where its indices can be represented by any single type, such as a string.

### Directories of Code:
1) **count_words.cpp** revisits the word counting program first estabished in the extension of Chapter 3. As before, it takes seqnences of words and outputs the number of occurances of each word. This time, however, it incorporates the map data structure to give an easier solution, while outputting the results in alphabetical order.
2) **x_ref** takes lines of text as input and outputs a cross-reference for each word in the text.

### Extension:
3) **sentence_generator** goes into much more depth in regards to maps and their potential. It takes as input lines of text that as a whole represent what is known as a grammar, used to define a language in a formal, organised way. Each line represents a rule specifying possible words and synatax the grammar allows.
From the inputted grammar, five sentences are generated randomly.

### New Concepts:
* The map data structure, as explained above.
* Iterators on maps, each pointing to an object which has two members refering to the key and the value respectively.
* Specifying default parameter values of a function.
* Recursion, using a function within itself to breaking down the problem being solved into smaller, more managable parts.
* Generating random numbers, as well as setting random seeds using the current time.
* do-while loops, essentially the same as while loops but the condition is checked AFTER the block of code in the loop is run.
