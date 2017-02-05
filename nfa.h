/*
 * File: nfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:54:41 2016
 * Time-stamp: <Mon Sep  5 15:42:16 EDT 2016 ferguson>
 */

#ifndef _nfa_h_gf
#define _nfa_h_gf

#include <stdbool.h>

// Assume input is 7-bit US-ASCII characters
#define NFA_NSYMBOLS 128

// Assume we start in state 0
#define NFA_START_STATE 0

// The transition function is represented as an array, indexed by input
// symbol, of the set of states reached on that symbol.
typedef struct {
    IntSet *transitions[NFA_NSYMBOLS];
    bool is_accepting;
} NFA_State;

// An NFA is an array of States (size TBD) and a set of possible current states
typedef struct {
    int nstates;
    NFA_State *states;
    IntSet *current_states;
} NFA;

extern NFA *NFA_new(int nstates);
extern void NFA_free(NFA *nfa);

extern int NFA_get_size(NFA *nfa);

extern IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol);
extern void NFA_add_transition(NFA *nfa, int src, char symbol, int dst);
extern void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst);
extern void NFA_add_transition_all(NFA *nfa, int src, int dst);

extern IntSet *NFA_get_current_states(NFA *nfa);
extern void NFA_set_current_states(NFA *nfa, IntSet *states);
extern void NFA_set_current_state(NFA *nfa, int state);
extern bool NFA_get_accepting(NFA *nfa, int statenum);
extern void NFA_set_accepting(NFA *nfa, int statenum, bool value);
extern bool NFA_is_accepting(NFA *nfa);

extern bool NFA_execute(NFA *nfa, char *input);

// True to enable tracing during NFA_Execute
extern int NFA_tracing;

#endif
