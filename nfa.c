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

//Creates and return a new NFA with the allotted number of states and all states set to non-accepting and with an IntSet assigned to each transition
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
//Frees the memory of the intsets in transitions, the int set of current states, the array of states, and the NFA itself
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

//Returns the number of states
int NFA_get_size(NFA *nfa) {
    return nfa->nstates;
}

//Returns the transition of the given symbol at the given statenum
IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
    return nfa->states[statenum].transitions[symbol];
}
//Creates a transition from the src to dst with the given symbol
void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
    IntSet_add(nfa->states[src].transitions[symbol], dst);
}
//Creates a transition from the src to dst that accepts any char of the given string str
void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i = 0; i < strlen(str); i++) {
        IntSet_add(nfa->states[src].transitions[str[i]], dst);
    }
}
//Creates a transtiton from src to dst that accepta all input (lambda)
void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for (int i = 0; i < NFA_NSYMBOLS; i++) {
        IntSet_add(nfa->states[src].transitions[i], dst);
    }
}

//Returns the intset storing current states
IntSet *NFA_get_current_states(NFA *nfa) {
    return nfa->current_states;
}
//Sets the current_states int set to the intset, states, given
void NFA_set_current_states(NFA *nfa, IntSet *states) {
    nfa->current_states = states;
}
//Sets the current state to the given state
void NFA_set_current_state(NFA *nfa, int state) {
    IntSet_add(nfa->current_states, state);
}
//Gets the accepting value of the given state number, statenum
bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->states[statenum].is_accepting;
}
//Sets the accepting value at the given state, statenum, to the given value
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->states[statenum].is_accepting = value;
}
//Returns the accepting value of the intset, true if any state is accepting, false otherwise
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

//Runs the NFA with the given input, uses a recurisve function to do so
bool NFA_execute(NFA *nfa, char *input) {
    return NFA_recursive_execute(nfa, input, nfa->current_states);
}

//The recursive function associated with NFA_execute that iterates through the given starting_states
bool NFA_recursive_execute(NFA *nfa, char *input, IntSet *starting_states) {
    //Iterator created
    IntSetIterator *current_iterator = IntSet_iterator(starting_states);
    //While-loop continues until nothing left to iterate to
    while(IntSetIterator_has_next(current_iterator)) {
        //New iterator, current, created
        int current = IntSetIterator_next(current_iterator);
        //If remaining string is not null
        if (strlen(input) > 0) {
            /*Recurse back through using a depth-first search
            One less input (because already used), and  iterates through the now current_states of the now current state*/
            bool tempBoolean = NFA_recursive_execute(nfa, (input+1), nfa->states[current].transitions[input[0]]);
            //If recursed value is true, free the iterator and return true
            if(tempBoolean) {
                free(current_iterator);
                return true;
            }
        //Else if the current state is accepting, free the iterator and return true
        } else if (nfa->states[current].is_accepting) {
            free(current_iterator);
            return true;
        }
    }
    //If all else fails, free the iterator and return false
    free(current_iterator);
    return false;
}

//I was unsure of the purpose of this in this context and as such did not use it
//int NFA_tracing {
//}

