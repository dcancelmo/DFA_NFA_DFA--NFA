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
#include <stdbool.h>
#include "IntSet.h"
#include "nfa.h"

NFA *NFA_new(int nstates) {
    NFA* newNFA = (NFA*)malloc(sizeof(NFA));
    newNFA->nstates = nstates;
    IntSet *begin = IntSet_new();
    IntSet_add(begin, 0);
    newNFA->states = (NFA_State*)malloc(nstates*sizeof(NFA_State));
    newNFA->current_states = begin;
    
    for (int i = 0; i < nstates; i++) {
        newNFA->states[i].is_accepting = false;
    }
    for (int i = 0; i < nstates; i++) {
        for(int j = 0; j < NFA_NSYMBOLS; j++) {
            newNFA->states[i].transitions[j] = IntSet_new();
        }
    }
    
    return newNFA;
}
void NFA_free(NFA *nfa) {
    for (int i = 0; i < nfa->nstates; i++) {
        NFA_State *curr_state = &nfa->states[i];
        for (int j = 0; j < NFA_NSYMBOLS; j++) {
            IntSet_free(curr_state->transitions[j]);
        }
    }
    IntSet_free(nfa->current_states);
    free(nfa->states);
    free(nfa);
}

int NFA_get_size(NFA *nfa) {
    return nfa->nstates;
}

IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
    return nfa->states[statenum].transitions[symbol];
}
void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
    IntSet_add(nfa->states[src].transitions[symbol], dst);
}
void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i = 0; i < strlen(str); i++) {
        IntSet_add(nfa->states[src].transitions[str[i]], dst);
    }
}
void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for (int i = 0; i < NFA_NSYMBOLS; i++) {
        IntSet_add(nfa->states[src].transitions[i], dst);
    }
}

IntSet *NFA_get_current_states(NFA *nfa) {
    return nfa->current_states;
}
void NFA_set_current_states(NFA *nfa, IntSet *states) {
    nfa->current_states = states;
}
void NFA_set_current_state(NFA *nfa, int state) {
    IntSet_add(nfa->current_states, state);
}
bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->states[statenum].is_accepting;
}
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->states[statenum].is_accepting = value;
}
bool NFA_is_accepting(NFA *nfa) {
    IntSetIterator *iter = IntSet_iterator(nfa->current_states);
    while(IntSetIterator_has_next(iter)) {
        if (nfa->states[IntSetIterator_next(iter)].is_accepting) {
            free(iter);
            return true;
        }
    }
    free(iter);
    return false;
}

bool NFA_execute(NFA *nfa, char *input) {
    
}

int NFA_tracing {
    
}

