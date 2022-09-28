# Chapter 5: Passing

An extension of the student records system established in [Chapter 4](../04_Records). It now distinguishes between students that passed and stutents that failed, based on their final grade being above or below a fixed threshold. The program uses 60 as the threshold.

### Directories of Code:
1) [`passing1`](passing1) outputs all the students with their final grades as usual, but adds "(fail)" next to every grade below the threshold, while making no comment on the passing grades.
2) [`passing2`](passing2) instead extracts the students that failed from the students that passed, and outputs a separate list for each of these two groups. Students that did not do homework are also put into the failed category. It also uses a list rather than a vector to store the student grades and then extract the failing students (see the comment at the end of [grade.cpp](passing2/grade.cpp)).
### Extension:
3) [`sentence_split`](sentence_split) does further experimentation with iterators. On every line, it receives a sentence as user input, splits it into a vector of its words (identified using the spaces in the sentence), then uses an iterator to output the words line by line.
4) [`concordance`](concordance) takes iterators and sentence splitting even further. It receives lines of phrases inputted by the user, and neatly generates a concordance for the every word that appears (including repeats).
5) [`framing1`](framing1) goes into more depth with creating a border around strings, along with padding. It represents a picture of characaters as a vector of strings, and constructs algorithms for framing them, and joining them vertically and horizontally. The actual program only asks the user to input lines of text, then outputs the text bordered by a frame.
6) [`framing2`](framing2) showcases the full capibilities of the algorithms constructed in [char_pic.cpp](framing1/char_pic.cpp). It creates a possible interface design for a Tetris-like game to demonstrate them.
### New Concepts:
* Using iterators to traverse over the elements of a data container while pointing to them.
* The dereference `*` operator, used to get the value that an iterator is pointing to.
* The `->` operator, used to get access a member of the value pointed to by an iterator (equivalent to `(*iterator).member_name`)
* Deleting an element of a container
* The `list` data structure, implementing a linked list.
* Determining which data container (particularly, vector or list) would be most efficient to use, by acknowleing their pros and cons.
* Reading a single line of input text.
* Creating a substring out of a given string.
* Converting integer to string, and padding with leading zeros.
* Pushing the contents of a vector into another (container "concatenation").
