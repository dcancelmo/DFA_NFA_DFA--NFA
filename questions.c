/*
 Daniel Cancelmo
 CSC 173 - Computation & Formal Systems
 Project 1
 Prof. Ferguson
 I attest that all work herein is my own and I did not collaborate with anyone.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "questions.h"
#include "dfa.h"


DFA *ab() {
    printf("Exactly the string 'ab'\n");
    DFA *dfaAB = DFA_new(3);
    DFA_set_transition(dfaAB, 0, 'a', 1);
    DFA_set_transition(dfaAB, 1, 'b', 2);
    DFA_set_accepting(dfaAB, 2, TRUE);
    DFA_print(dfaAB);
    printf("ab: %d\n", DFA_execute(dfaAB, "ab"));
    printf("abc: %d\n", DFA_execute(dfaAB, "abc"));
    printf("zabd: %d\n", DFA_execute(dfaAB, "zabd"));
    printf("cd: %d\n", DFA_execute(dfaAB, "cd"));
    
    return dfaAB;
}

DFA *ab_begin() {
    printf("Strings starting with 'ab'\n");
    DFA *dfaAB_begin = DFA_new(3);
    DFA_set_transition(dfaAB_begin, 0, 'a', 1);
    DFA_set_transition(dfaAB_begin, 1, 'b', 2);
    DFA_set_transition_all(dfaAB_begin, 2, 2);
    DFA_set_accepting(dfaAB_begin, 2, TRUE);
    DFA_print(dfaAB_begin);
    printf("abc: %d\n", DFA_execute(dfaAB_begin, "abc"));
    printf("zab: %d\n", DFA_execute(dfaAB_begin, "zab"));
    printf("asdf: %d\n", DFA_execute(dfaAB_begin, "asdf"));
    printf("cd: %d\n", DFA_execute(dfaAB_begin, "cd"));
    printf("cdab: %d\n", DFA_execute(dfaAB_begin, "cdab"));
    
    return dfaAB_begin;
}

DFA *even1() {
    printf("Binary strings with an even number of 1s\n");
    DFA *dfa_even = DFA_new(3);
    DFA_set_transition(dfa_even, 0, '1', 1);
    DFA_set_transition(dfa_even, 1, '1', 2);
    DFA_set_transition(dfa_even, 2, '1', 1);
    DFA_set_transition(dfa_even, 0, '0', 0);
    DFA_set_transition(dfa_even, 1, '0', 1);
    DFA_set_transition(dfa_even, 2, '0', 2);
    DFA_set_accepting(dfa_even, 0, TRUE);
    DFA_set_accepting(dfa_even, 2, TRUE);
    DFA_print(dfa_even);
    printf("011: %d\n", DFA_execute(dfa_even, "011"));
    printf("110: %d\n", DFA_execute(dfa_even, "110"));
    printf("101: %d\n", DFA_execute(dfa_even, "101"));
    printf("01011: %d\n", DFA_execute(dfa_even, "01011"));

    return dfa_even;
}

DFA *even1even2() {
    printf("Binary strings with an even number of 1s\n");
    DFA *dfa_even = DFA_new(4);
    DFA_set_transition(dfa_even, 0, '0', 1);
    DFA_set_transition(dfa_even, 1, '0', 0);
    DFA_set_transition(dfa_even, 2, '0', 3);
    DFA_set_transition(dfa_even, 3, '0', 2);
    DFA_set_transition(dfa_even, 0, '1', 3);
    DFA_set_transition(dfa_even, 3, '1', 0);
    DFA_set_transition(dfa_even, 1, '1', 2);
    DFA_set_transition(dfa_even, 2, '1', 1);
    DFA_set_accepting(dfa_even, 0, TRUE);
    DFA_print(dfa_even);
    printf("011: %d\n", DFA_execute(dfa_even, "011"));
    printf("1010: %d\n", DFA_execute(dfa_even, "1010"));
    printf("101: %d\n", DFA_execute(dfa_even, "101"));
    printf("101011: %d\n", DFA_execute(dfa_even, "101011"));
    printf("01011: %d\n", DFA_execute(dfa_even, "01011"));
    
    return dfa_even;
}

DFA *prefix() {
    printf("Strings that start with 'mr.', 'mrs.', 'miss', and 'ms.'\n");
    DFA *prefix = DFA_new(8);
    DFA_set_transition(prefix, 0, 'm', 1);
    DFA_set_transition(prefix, 1, 'r', 2);
    DFA_set_transition(prefix, 2, 's', 3);
    DFA_set_transition(prefix, 2, '.', 4);
    DFA_set_transition(prefix, 3, '.', 4);
    DFA_set_transition(prefix, 1, 'i', 5);
    DFA_set_transition(prefix, 5, 's', 6);
    DFA_set_transition(prefix, 6, 's', 4);
    DFA_set_transition(prefix, 1, 's', 7);
    DFA_set_transition(prefix, 7, '.', 4);
    DFA_set_transition_all(prefix, 4, 4);
    DFA_set_accepting(prefix, 4, TRUE);
    DFA_print(prefix);
    printf("mr. k: %d\n", DFA_execute(prefix, "mr. k"));
    printf("mrs. q: %d\n", DFA_execute(prefix, "mrs. q"));
    printf("miss l: %d\n", DFA_execute(prefix, "miss l"));
    printf("ms. c: %d\n", DFA_execute(prefix, "ms. c"));
    printf("dr. f: %d\n", DFA_execute(prefix, "dr. f"));
    
    return prefix;
}

