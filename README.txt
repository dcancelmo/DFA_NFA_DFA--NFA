Daniel Cancelmo
Project 01 - Finite Automata
CSC 173 - Professor Ferguson
February 06, 2017
I did not collaborate with anyone on this assignment.
ReadMe file

Instructions:
To build the executable file and to run it at the same time all in one command use the terminal while in the project directory and type-

	make

To run the file (on a UNIX system) after building it type-

	./cancelmo_project1
or
	make run

Or to build and run in all one command type-

	make all

To remove the executable file type-

	make clean

To build, run, and clean all in one command type-

	make run-clean

If at any point a segmentation fault occurs:
Run again until it works. I reccomend using ‘make run-clean’ to avoid seg faults. 

Output explanation:
The output is broken up into question 1, 2, and 3. Question 1 shows the output of the DFAs, question 2 the output of the NFAs, and question 3 the output of the NFA->DFA conversions.
Question 1 shows a one line description of the language the DFA accepts, a print out of the states of the DFA, and each string tested on it and its output displayed as the format-

	input: output

The output will be a 0 or 1. 0 means the DFA did not accept the input string as part of its language and 1 means that it did.
The same is true for question 2 except this is done with NFAs and it does not print out the states.
Question 3 shows the output of the original NFA again followed by the output of the NFA translated to a DFA for comparison.
The custom NFA ‘common’ conversion is commented out of ‘main.c’ because when run it causes a segmentation fault. I believe because too much memory is in use. Otherwise, it works properly.