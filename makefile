# The makefile for MP5.
# Type:
#   make         -- to build program lab5
#
#
# Format for each entry
#    target : dependency list of targets or files
#    <tab> command 1
#    <tab> command 2
#    ...
#    <tab> last command
#    <blank line>   -- the list of commands must end with a blank line

lab5 : bst.o lab5.o lab5.c bst.c bst.h
	gcc -Wall -g bst.o lab5.o -o lab5 -lm

bst.o : bst.c lab5.c
	gcc -Wall -g -c bst.c

lab5.o : lab5.c bst.h 
	gcc -Wall -g -c lab5.c
 

