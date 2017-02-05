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
#include "dfa.h"

//Creates and returns a new DFA with the allotted number of states, no transitions, and all states set to non-accepting
DFA *DFA_new(int nstates) {
    DFA* newDFA = (DFA*)malloc(sizeof(DFA));
    newDFA->nstates = nstates;
    newDFA->states = (DFA_State*)malloc(nstates*sizeof(DFA_State));
    newDFA->current_state = DFA_START_STATE;
    
    for (int i = 0; i < nstates; i++) {
        newDFA->states[i].is_accepting = FALSE;
    }
    for (int i = 0; i < nstates; i++) {
        for(int j = 0; j < DFA_NSYMBOLS; j++) {
            newDFA->states[i].transitions[j] = DFA_NO_TRANSITION;
        }
    }
    
    return newDFA;
}

//Frees memory of the dfa's states and the dfa as a whole
void DFA_free(DFA *dfa) {
    for (int i = 0; i < dfa->nstates; i++) {
        free(dfa->states->transitions);
    }
    free(dfa->states);
    free(dfa);
}

//Getter for size of DFA (num of states)
int DFA_get_size(DFA *dfa) {
    return dfa->nstates;
}

//Transition getters and setters
int DFA_get_transition(DFA *dfa, int statenum, char symbol) {
    return dfa->states[statenum].transitions[symbol];
}
void DFA_set_transition(DFA *dfa, int src, char symbol, int dst) {
    dfa->states[src].transitions[symbol] = dst;
}
void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst) {
    for(int i = 0; i < strlen(str); i++) {
        dfa->states[src].transitions[str[i]] = dst;
    }
}
void DFA_set_transition_all(DFA *dfa, int src, int dst) {
    for (int i = 0; i < DFA_NSYMBOLS; i++) {
        dfa->states[src].transitions[i] = dst;
    }
}

//State getters and setters
int DFA_get_current_state(DFA *dfa) {
    return dfa->current_state;
}
void DFA_set_current_state(DFA *dfa, int statenum) {
    dfa->current_state = statenum;
}
int DFA_get_accepting(DFA *dfa, int statenum) {
    return dfa->states[statenum].is_accepting;
}
void DFA_set_accepting(DFA *dfa, int statenum, int value) {
    dfa->states[statenum].is_accepting = value;
}

//Returns a value whether or not the current state is accepting
int DFA_is_accepting(DFA *dfa) {
    return dfa->states[dfa->current_state].is_accepting;
}


//Runs the DFA passed into it with the input string passed into it
int DFA_execute(DFA *dfa, char *input) {
    for (int i = 0; i < strlen(input); i++) {
        //printf("input: %d\n", dfa->states[dfa->current_state].transitions[input[i]]);
        //printf("%d\n", dfa->current_state);
        int next_state = dfa->states[dfa->current_state].transitions[input[i]];
        DFA_set_current_state(dfa, next_state);
        //Halts program if no transition
        if (dfa->current_state == DFA_NO_TRANSITION) {
            //printf("Test\n");
            return FALSE;
        }

    }
    int ending_state = DFA_get_current_state(dfa);
    //Resets DFA
    DFA_set_current_state(dfa, DFA_START_STATE);
    //Returns if the ending state is an accepting state or not
    return DFA_get_accepting(dfa, ending_state);
}

//Prints each state of the array, whether it is accepting or not and its transitions
void DFA_print(DFA *dfa) {
    
    for (int i = 0; i < DFA_get_size(dfa); i++) {
        if (dfa->states[i].is_accepting == TRUE) {
            printf("State: %d\tAccepting?: Yes\tTransitions:", i);
        } else {
            printf("State: %d\tAccepting?: No\tTransitions:", i);
        }
        
        int transCount = 0;
        for (int j = 0; dfa->states[i].transitions[j] != '\0'; j++) {
            if (dfa->states[i].transitions[j] != DFA_NO_TRANSITION) {
                transCount += 1;
            }
        }
        if (transCount >= DFA_NSYMBOLS) {
            printf(" All characters");
        } else {
            for (int j = 0; dfa->states[i].transitions[j] != '\0'; j++) {
                if (dfa->states[i].transitions[j] != DFA_NO_TRANSITION) {
                    char c = j;
                    if (c != '\200') {
                        printf(" %c", c);
                    }
                }
            }
        }
        
        printf("\n");
        
    }
    
}
