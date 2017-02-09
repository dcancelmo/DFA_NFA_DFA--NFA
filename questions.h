/*
 Daniel Cancelmo
 CSC 173 - Computation & Formal Systems
 Project 1
 Prof. Ferguson
 I attest that all work herein is my own and I did not collaborate with anyone.
 */

#ifndef questions_h
#define questions_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "NFA-DFA.h"

extern DFA *ab();
extern DFA *ab_begin();
extern DFA *even1();
extern DFA *even1even2();
extern DFA *prefix();
extern NFA *man();
extern NFA *washington();
extern NFA *common();
extern DFA *convert(NFA *nfa, char* name);


#endif /* questions_h */
