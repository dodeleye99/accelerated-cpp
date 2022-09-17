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
OBJECTS := $(addprefix $(OBJ)/, \
			main.o nrand.o split.o)

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
						nrand.h split.h)
	$(CC) -o $@ -c $<

$(OBJ)/nrand.o:			$(SRC)/nrand.cpp $(call src_deps, \
						nrand.h)
	$(CC) -o $@ -c $<

$(OBJ)/split.o:			$(SRC)/split.cpp $(call src_deps, \
						split.h)
	$(CC) -o $@ -c $<

# Special target for reserving names as recipes, ignoring files with
# the same names that might appear in the directory.
.PHONY: all clean

# Delete all the files that the Makefile generates 
# (by running 'make clean')
clean:
	rm -f $(BIN)/$(TARGET) $(OBJ)/*.o