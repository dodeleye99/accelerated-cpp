# ******************************************************************
# --- Introduction to Makefiles ---
# A Makefile provides a convenient way to compile a program 
# (or do other building tasks) under a single command 'make'. It does 
# this by setting rules that specify how to create a single 
# executable file out of source code.
#
# *******************************************************************
# --- GENERAL SYNTAX FOR RULES ---
# target: pre-req1 pre-req 2 pre-req3 ...
# <tab> recipe1
#		recipe2
#		recipe3
#       ...
#
# where <tab> represents an entered tab ('\t') - ESSENTIAL for the 
# recipe to be recognised as part of the rule
#
# --- RULE COMPONENTS ---
# target 		- the "thing" that is to be made. It could be a file,
#				  an executable, or simply an action.
#
# prerequisites	- the list of "things" that must be made before the 
#				  target (in other words, its dependencies).
#
# recpies		- the sequence of commands used to make the target.
# *******************************************************************

# --- RULES ---

# Compile main.cpp (that is, transform it into machine code), 
# writting results to a new (executable) file called "main".
main: main.cpp
	g++ -o main main.cpp

# *******************************************************************
# Running 'make' in the command line will run the command
#				
#				 g++ -o main main.cpp
#
# only in the following cases:
# 1) 'main' does not exist
# 2) 'main' exists, but 'main.cpp' is newer than 'main' 
#	 (i.e source code has been changed)
# 
# Otherwise it will do nothing.
# *******************************************************************