/*
 Daniel Cancelmo
 CSC 173 - Computation & Formal Systems
 Project 1
 Prof. Ferguson
 I attest that all work herein is my own and I did not collaborate with anyone.
 */

#ifndef NFA_DFA_h
#define NFA_DFA_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"
#include "dfa.h"
#include "nfa.h"
#include "LinkedList.h"
#include "IntSet.h"


extern DFA *NFA_DFA_Convert(NFA *nfa);
extern DFA_State *DFAState();

#endif /* NFA_DFA_h */
