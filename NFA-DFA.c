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
#include "NFA-DFA.h"
#include "questions.h"
#include "dfa.h"
#include "nfa.h"
#include "LinkedList.h"

//Converts and returns a DFA from a givn NFA
DFA *NFA_DFA_Convert(NFA *nfa) {
    //Lists for storing the states and intsets
    LinkedList *statesList = LinkedList_new();
    LinkedList *intSetsList = LinkedList_new();
    DFA_State *state_0 = DFAState();
    int nstates = 1;
    //State_0 added to the front of the list for states and iterator created for the list
    LinkedList_add_at_front(statesList, state_0);
    LinkedListIterator *statesList_iter = LinkedList_iterator(statesList);
    IntSet *set_0 = IntSet_new();
    IntSet_add(set_0, 0);
    //set_0 added to front of the list for intsets and iterator created for this list
    LinkedList_add_at_front(intSetsList, set_0);
    LinkedListIterator *intSetsList_iter = LinkedList_iterator(intSetsList);
    
    //While there exists more states
    while (LinkedListIterator_has_next(statesList_iter)) {
        DFA_State *curr_state = LinkedListIterator_next(statesList_iter);
        IntSet *curr_intSet = LinkedListIterator_next(intSetsList_iter);
        //Loop through all possible transition states
        for (int i = 0; i < NFA_NSYMBOLS; i++) {
            IntSet *dest = IntSet_new();
            IntSetIterator *curr_intSet_iter = IntSet_iterator(curr_intSet);
            //While there is another state in the nfa
            while (IntSetIterator_has_next(curr_intSet_iter)) {
                int temp = IntSetIterator_next(curr_intSet_iter);
                IntSet_union(dest, nfa->states[temp].transitions[i]);
                if (nfa->states[temp].is_accepting) {
                    curr_state->is_accepting = true;
                }
            }
            free(curr_intSet_iter);
            
            int contains = -1;
            int iteration = 0;
            LinkedListIterator *temp = LinkedList_iterator(intSetsList);
            //While there exists another intset in the list
            while(LinkedListIterator_has_next(temp)) {
                IntSet *tempIntSet = LinkedListIterator_next(temp);
                //If the tempintset is equal to the destination
                if(IntSet_equals(tempIntSet, dest)) {
                    contains = iteration;
                }
                iteration++;
            }
            free(temp);
            
            //If dest is unseen before, add
            if(contains < 0) {
                if (!(IntSet_is_empty(dest))) {
                    DFA_State *newState = DFAState();
                    curr_state->transitions[i] = nstates;
                    LinkedList_add_at_end(statesList, newState);
                    LinkedList_add_at_end(intSetsList, dest);
                    nstates += 1;
                }
            //Else if current state has former state as a transition
            } else if (!(IntSet_is_empty(dest))) {
                curr_state->transitions[i] = contains;
            }
        }
    }
    //Create the DFA and copy in all of its data
    DFA *newDFA = DFA_new(nstates);
    LinkedListIterator *final_states = LinkedList_iterator(statesList);
    for(int j = 0; j < nstates; j++) {
        DFA_State *temp_state = LinkedListIterator_next(final_states);
        newDFA->states[j] = *temp_state;
        free(temp_state);
    }
    //Free remainig lists and iterators and return the new_DFA
    free(intSetsList_iter);
    free(final_states);
    free(statesList_iter);
    return newDFA;
}

//Create a new DFA state, adapted from code in DFA.c
DFA_State *DFAState() {
    DFA_State *new_State = (DFA_State*)malloc(sizeof(DFA_State));
    new_State->is_accepting = FALSE;
    for(int i = 0; i < NFA_NSYMBOLS; i++) {
        new_State->transitions[i] = DFA_NO_TRANSITION;
    }
    return new_State;
}
