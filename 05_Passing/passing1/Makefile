# ******************************************************************
# --- INTRODUCTION TO VARIABLES ---
# As in programming languages, Makefiles allow one to define 
# variables. The value of a variable is a string of text, which
# replaces the variable whenever it is referenced in any part of a 
# rule or another variable.
#
# The syntax for calling a variable is 
#		$(<VARIABLE_NAME>) or ${<VARIABLE-NAME>}
#
# There are two ways to define a variable:
# 1) VARIABLE_NAME = value	(recursively-expanded variables)
# 2) VARIBLE_NAME := value	(simply-expanded variables)
#
# In the first method, the variable does not actually hold the
# value statically. It retrieves the value upon every call, which 
# allows it to refer to variables with values known only during 
# "runtime".
# 
# In the second method, the variable is static, refers to the value 
# at the time it was defined, just as in programming languages. Thus
# its behaviour is more predicatable.
# 
# One may also define multi-line variables of the first kind by the
# following syntax:
# 	define VARIABLE_NAME
# 	...
# 	endef
# ******************************************************************
# --- VARIABLES AS FUNCTIONS ---
# One may also create variables (of the first kind) that act as 
# functions, taking a set of string arguments and outputting text 
# from those arguments.
#
# To refer to an argument, write $(n), where n refers to the nth 
# argument passed.
#
# The syntax for calling the variable as a function is 
#		$(call <variable>, arg_1, arg_2, ...)
# ******************************************************************

# --- VARIABLES ---

# The compiler to use for making the exectutable file.
CC := g++

# Compiler flags:
#  -g     - adds debugging information to the executable file
#  -Wall  - used to turn on most compiler warnings
CFLAGS  := -g -Wall

# The base name of the file the compiler will write the executable.
TARGET := main

# The directory of the source code files.
SRC := src

# The directory to store the executable.
BIN := bin

# The directory to store the object files.
OBJ := obj

# The object (machine code) files to create from the source files.
OBJECTS := $(addprefix $(OBJ)/, main.o student_info.o median.o grade.o)

# A function that adds the source directory as the prefix of every
# 	name in the list passed to it, presumably of header files.
# This ensures that they are obtained from the correct directory.
src_deps  = $(addprefix $(SRC)/, $(1))

# --- RULES ---

# The default rule that will be run if none is specified immediately
# 	after the 'make' command. 
# It will attempt to build the executable.
all: $(TARGET)

# Creating executable file, first compiling the object files and then
# linking them to make the executable.
$(TARGET): 	$(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN)/$(TARGET) $^

# -- Compiling object files --
$(OBJ)/main.o:			$(SRC)/main.cpp $(call src_deps, \
						grade.h median.h Student_info.h)
	$(CC) -o $@ -c $<

$(OBJ)/grade.o:			$(SRC)/grade.cpp $(call src_deps, \
						grade.h median.h Student_info.h)
	$(CC) -o $@ -c $<

$(OBJ)/median.o:		$(SRC)/median.cpp $(call src_deps, \
						median.h)
	$(CC) -o $@ -c $<

$(OBJ)/student_info.o: 	$(SRC)/student_info.cpp $(call src_deps, \
						Student_info.h)
	$(CC) -o $@ -c $<


# Special target for reserving names as recipes, ignoring files with
# the same names that might appear in the directory.
.PHONY: all clean

# Delete all the files that the Makefile generates 
# (by running 'make clean')
clean:
	rm -f $(BIN)/$(TARGET) $(OBJ)/*.o

# *******************************************************************
# === COMPILE OPTIONS ===
#
# -o <file>: Used to specify the output file to place the compiled 
#			 code in.
#
# -c: 		 Compiles or assembles the source files (.cpp) BUT does 
#			 NOT link. That is, it does not form an executable file, 
#  			 but only an object file. It may LATER be linked with 
#			 other object files to form the final executable.
# *******************************************************************
# === WILDCARDS ===
# A single string of text can be used to cover multiple file names by
# specifying what are known as wildcard characters.
#
# EXAMPLES:
# *.cpp: used to repreesnt every source file (.cpp) in the directory
# 
# === AUTOMATIC VARIABLES ===
# $@: the file name of the target of the rule
# $<: the name of the FIRST prereiquisite
# $^: the names of ALL prerequisites
# *******************************************************************
# The compiling and linking process can be thought of as a "grammar":
# <all> 		   <main>
# <main> 	       g++ -o main main.cpp <grade.o> <median.o> 
# 										<student_info.o>
#
# <grade.o>        g++ -c grade.cpp (grade.h Student_info.h median.h)
# <median.o>       g++ -c median.cpp (median.h)
# <student_info.o> g++ -c student_info.cpp (Student_info.h)
# *******************************************************************