# Chapter 5: Passing

An extension of the student records system established in Chapter 4. It now distinguishes between students that passed and stutents that failed, based on their final grade being above or below a fixed threshold. The program uses 60 as the threshold.

### Directories of Code:
1) **passing1** outputs all the students with their final grades as usual, but adds "(fail)" next to every grade below the threshold, while making no comment on the passing grades.
2) **passing2** instead extracts the students that failed from the students that passed, and outputs a separate list for each of these two groups. Students that did not do homework are also put into the failed category. It also uses a list rather than a vector to store the student grades and then extract the failing students (see the comment at the end of **passing2/grades.cpp**).
### Extension:
3) **sentence_split** does further experimentation with iterators. On every line, it receives a sentence as user input, splits it into a vector of its words (identified using the spaces in the sentence), then uses an iterator to output the words line by line.
4) **concordance** takes iterators and sentence splitting even further. It receives lines of phrases inputted by the user, and neatly generates a concordance for the every word that appears (including repeats).
### New Concepts:
* Using iterators to traverse over the elements of a data container while pointing to them.
* The * operator, used to get the value that an iterator is pointing to.
* The -> operator, used to get access a member of the value pointed to by an iterator (equivalent to (*iterator).member_name)
* Deleting an element of a container
* The list data structure, implementing a linked list.
* Determining which data container (particularly, vector or list) would be most efficient to use, by acknowleing their pros and cons.
* Reading an single line of input text.
* Creating a substring out of a given string.
* Converting integer to string, and padding with leading zeros.
