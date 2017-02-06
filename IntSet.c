/*
 * File: IntSet.c
 * Creator: George Ferguson
 * Created: Fri Jul  1 09:51:18 2016
 * Time-stamp: <Wed Sep  7 17:58:37 EDT 2016 ferguson>
 *
 * Implementation of Set of ints as a simple linked list.
 * Adding to the set means adding at the front since that's cheapest.
 * Lookup (and hence add) is linear-time. You could do much better...
 */

#include <stdio.h>
#include <stdlib.h>
#include "IntSet.h"

/**
 * Toplevel structure for an IntSet.
 * This implementation simply uses a linked list.
 */
struct IntSet {
    struct IntSetNode *first;
    struct IntSetNode *last;
};
    
/**
 * Structure for each element in an IntSet, stored as a linked list.
 */
typedef struct IntSetNode {
    int value;
    struct IntSetNode *next;
} IntSetNode;

/**
 * Allocate, initialize and return a new (empty) IntSet.
 */
IntSet *
IntSet_new() {
    IntSet *set = (IntSet*)malloc(sizeof(IntSet));
    set->first = set->last = NULL;
    return set;
}

/**
 * Free the memory used for the given IntSet and all its elements.
 */
void
IntSet_free(IntSet *set) {
    // Free the elements
    IntSetNode *elt = set->first;
    while (elt != NULL) {
	IntSetNode *next = elt->next;
	free(elt);
	elt = next;
    }
    // Free the set (list)
    free(set);
}

/**
 * Allocate and initialize a new IntSetNode storing the given int value.
 */
static IntSetNode *
IntSetNode_new(int value) {
    IntSetNode *node = (IntSetNode*)malloc(sizeof(IntSetNode));
    if (node == NULL) {
	abort();
    }
    node->value = value;
    node->next = NULL;
    return node;
}

/**
 * Return true if the given IntSet is empty.
 */
bool
IntSet_is_empty(const IntSet *set) {
    return set->first == NULL;
}

/**
 * Add given int to the given IntSet (if it's not already there).
 */
void
IntSet_add(IntSet *set, int value) {
    if (!IntSet_contains(set, value)) {
	// Add at front
	IntSetNode *node = IntSetNode_new(value);
	node->next = set->first;
	set->first = node;
    }
}

/**
 * Return true if the given IntSet contains the given int value.
 */
bool
IntSet_contains(const IntSet *set, int value) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	if (node->value == value) {
	    return true;
	}
    }
    return false;
}

/**
 * Add the contents of IntSet set2 to IntSet set1 (adding those elements
 * that aren't already in set1). This will modify set1 unless set2 is empty
 * (or all its elements are already in set1).
 */
void
IntSet_union(IntSet *set1, const IntSet *set2) {
    for (IntSetNode *node=set2->first; node != NULL; node=node->next) {
	IntSet_add(set1, node->value);
    }
}

/**
 * Return true if the first IntSet contains every member of the second
 * IntSet.
 */
bool
IntSet_contains_all(IntSet *set1, IntSet *set2) {
    for (IntSetNode *node2=set2->first; node2 != NULL; node2=node2->next) {
	if (!IntSet_contains(set1, node2->value)) {
	    return false;
	}
    }
    return true;
}
    
/**
 * Return true if the two given IntSets contain exactly the same members,
 * otherwise false.
 */
bool
IntSet_equals(IntSet *set1, IntSet *set2) {
    return IntSet_contains_all(set1, set2) && IntSet_contains_all(set2, set1);
}

/**
 * Call the given function on each element of given IntSet, passing the
 * int value to the function.
 */
void
IntSet_iterate(const IntSet *set, void (*func)(int)) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	func(node->value);
    }
}

struct IntSetIterator {
    IntSetNode *node;
};

/**
 * Return an IntSetIterator for the given IntSet.
 * Don't forget to free() this when you're done iterating.
 */
IntSetIterator *
IntSet_iterator(const IntSet *set) {
    IntSetIterator *iterator = (IntSetIterator*)malloc(sizeof(IntSetIterator));
    iterator->node = set->first;
    return iterator;
}

/**
 * Return the next int from the given IntSetIterator and increment it
 * to point to the next element.
 * This will cause a crash if there is no such element.
 * You could make a safe version with a pass-by-reference (int*) parameter
 * for the int and boolean return value that indicates whether the operation
 * succeeded or not. Ah, the goold old days...
 */
bool
IntSetIterator_has_next(const IntSetIterator *iterator) {
    return iterator != NULL && iterator->node != NULL;
}

int
IntSetIterator_next(IntSetIterator *iterator) {
    if (iterator == NULL || iterator->node == NULL) {
	abort();
    } else {
	int value = iterator->node->value;
	iterator->node = iterator->node->next;
	return value;
    }
}

/**
 * Print the given IntSet to stdout.
 */
void
IntSet_print(IntSet *set) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	printf("%d", node->value);
	if (node->next != NULL) {
	    printf(" ");
	}
    }
    printf("\n");
}
