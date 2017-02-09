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
#include "nfa.h"
#include "NFA-DFA.h"

int main(int argc, char* argv[]) {
    
    printf("__QUESTION 1__\n");
    free(ab());
    free(ab_begin());
    free(even1());
    free(even1even2());
    free(prefix());
    printf("\n__QUESTION 2__\n");
    free(man());
    free(washington());
    free(common());
    printf("\n__QUESTION 3__\n");
    free(convert(man(), "man"));
    //free(man);
    free(convert(washington(), "washington"));
    //free(washington);
    //free(convert(common(), "common"));
    //free(common);
    return 0;
}
