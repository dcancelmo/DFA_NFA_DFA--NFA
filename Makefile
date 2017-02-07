#Created by Daniel Cancelmo
#CSC 173 -Professor Ferguson
#Project 01 - Finite Automata
#MakeFile to create an executable that creates and tests: 
#DFAs, NFAs, and NFA->DFA Conversion

CC=gcc
CFLAGS = o
FILES = main.c LinkedList.c IntSet.c nfa.c dfa.c questions.c
EXECUTABLE = cancelmo_project1
CUSTOM = 

make : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)

run : 
	./$(EXECUTABLE)

all : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)
	./$(EXECUTABLE)

clean : 
	rm $(EXECUTABLE)

run-clean : $(FILES)
	$(CC) -$(CFLAGS) $(EXECUTABLE) $(FILES)
	./$(EXECUTABLE)
	rm $(EXECUTABLE)
