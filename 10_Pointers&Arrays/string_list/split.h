#ifndef GUARD_split_h
#define GUARD_split_h

#include "String_list.h"
#include <string>

/**
 * ------------------------------------------------------------------------------
 * This function template represents a family of functions which splits a string
 *  with respect to the spaces found within it, and writes each split part to an
 *  (assumed but not strictly necessary) output iterator.
 * ------------------------------------------------------------------------------
 * The 'Out' type-parameter: represents an output (i.e. write-only) iterator,
 *  which points to a single value of some sequence of elements at a time, 
 *  which can be reassigned but not read.
 **/
template <class Out>
void split(const std::string&, Out);

// outputs a String_list object consisting of the words split from a sentence.
String_list split(const std::string& str);

#endif