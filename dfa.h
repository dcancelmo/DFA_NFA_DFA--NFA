/*
 * File: dfa.h
 * Creator: George Ferguson
 * Created: Thu Sep  1 17:45:52 2016
 * Time-stamp: <Mon Sep  5 15:55:01 EDT 2016 ferguson>
 */

#ifndef _dfa_h_gf
#define _dfa_h_gf

// Could also use <stdbool.h> and true/false
#ifndef TRUE
# define TRUE 1
#endif
#ifndef FALSE
# define FALSE 0
#endif

// Assume input is 7-bit US-ASCII characters
#define DFA_NSYMBOLS 128

// Assume we start in state 0
#define DFA_START_STATE 0

// Entry in a transition table indicating ``no transition''
#define DFA_NO_TRANSITION -1

// Each state is a row in a transition table, and an `accepting' flag
typedef struct {
    int transitions[DFA_NSYMBOLS];
    int is_accepting;
} DFA_State;

// A DFA is an array of States (size TBD) and the current state
typedef struct {
    int nstates;
    DFA_State *states;
    int current_state;
} DFA;

extern DFA* DFA_new(int nstates);
extern void DFA_free(DFA *dfa);

extern int DFA_get_size(DFA *dfa);

extern int DFA_get_transition(DFA *dfa, int statenum, char symbol);
extern void DFA_set_transition(DFA *dfa, int src, char symbol, int dst);
extern void DFA_set_transition_str(DFA *dfa, int src, char *str, int dst);
extern void DFA_set_transition_all(DFA *dfa, int src, int dst);

extern int DFA_get_current_state(DFA *dfa);
extern void DFA_set_current_state(DFA *dfa, int statenum);
extern int DFA_get_accepting(DFA *dfa, int statenum);
extern void DFA_set_accepting(DFA *dfa, int statenum, int value);
extern int DFA_is_accepting(DFA *dfa);

extern int DFA_execute(DFA *dfa, char *input);

extern void DFA_print(DFA *dfa);

#endif
