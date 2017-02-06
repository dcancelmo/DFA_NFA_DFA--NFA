/*
 * File: LinkedList.c
 * Creator: George Ferguson
 * Created: Thu Jun 30 14:47:12 2016
 * Time-stamp: <Wed Sep  7 18:00:07 EDT 2016 ferguson>
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/**
 * Toplevel LinkedList structure.
 */
struct LinkedList {
    struct LinkedListNode *first;
    struct LinkedListNode *last;
};

/**
 * Structure for each element of a doubly-linked LinkedList.
 */
typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

/**
 * Allocate, initialize and return a new (empty) LinkedList.
 */
LinkedList *
LinkedList_new() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->first = list->last = NULL;
    return list;
}

static LinkedListNode *
LinkedListNode_new(void *data) {
    LinkedListNode *node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
	abort();
    }
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

/**
 * Free the memory used for the given LinkedList.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
void
LinkedList_free(LinkedList *list, bool free_data_also) {
    // Free the elements
    LinkedListNode *elt = list->first;
    while (elt != NULL) {
	LinkedListNode *next = elt->next;
	if (free_data_also && elt->data != NULL) {
	    free(elt->data);
	}
	free(elt);
	elt = next;
    }
    // Free the list itself
    free(list);
}

/**
 * Return true if the given LinkedList is empty.
 */
bool
LinkedList_is_empty(const LinkedList *list) {
    return list->first == NULL;
}

/**
 * Add the given void* value at the front of the given LinkedList.
 */
void
LinkedList_add_at_front(LinkedList *list, void *data) {
    LinkedListNode *node = LinkedListNode_new(data);
    node->next = list->first;
    if (list->first != NULL) {
	list->first->prev = node;
    }
    list->first = node;
    if (list->last == NULL) {
	list->last = node;
    }
}

/**
 * Add the given void* value at the end of the given LinkedList.
 */
void
LinkedList_add_at_end(LinkedList *list, void *data) {
    LinkedListNode *node = LinkedListNode_new(data);
    node->prev = list->last;
    if (list->last != NULL) {
	list->last->next = node;
    }
    list->last = node;
    if (list->first == NULL) {
	list->first = node;
    }
}

/**
 * Return true if then given LinkedList contains given void* value.
 */
bool
LinkedList_contains(const LinkedList *list, void *data) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	if (node->data == data) {
	    return true;
	}
    }
    return false;
}

/**
 * Remove the given void* value from the given LinkedList if it is there.
 * Note that this does not free the data associated with the element.
 */
void
LinkedList_remove(LinkedList *list, void *data) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	if (node->data == data) {
	    if (node == list->first) {
		list->first = node->next;
	    }
	    if (node == list->last) {
		list->last = node->prev;
	    }
	    if (node->prev != NULL) {
		node->prev->next = node->next;
	    }
	    if (node->next != NULL) {
		node->next->prev = node->prev;
	    }
	    free(node);
	    return;
	}
    }
}    

/**
 * Return the void* value at the given index in the given LinkedList, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a LinkedList. C'est la vie.
 */
void *
LinkedList_element_at(LinkedList *list, int index) {
    int i = 0;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	if (i == index) {
	    return node->data;
	}
	i += 1;
    }
    return NULL;
}

/**
 * Remove and return the first element from the given LinkedList.
 * Returns NULL if the list is empty.
 */
void *
LinkedList_pop(LinkedList *list) {
    void *data = LinkedList_element_at(list, 0);
    if (data != NULL) {
	LinkedList_remove(list, data); // Removes first occurrence
    }
    return data;
}

/**
 * Call the given function on each element of given LinkedList, passing the
 * void* value to the function.
 */
void
LinkedList_iterate(const LinkedList *list, void (*func)(void *)) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	func(node->data);
    }
}

/**
 * Return an LinkedListIterator for the given LinkedList.
 * Don't forget to free() this when you're done iterating.
 */
LinkedListIterator *
LinkedList_iterator(const LinkedList *list) {
    LinkedListIterator *iterator = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
    *iterator = list->first;
    return iterator;
}

/**
 * Return true if the given LinkedListIterator will return another element
 * if LinkedListIterator_next() is called.
 */
bool
LinkedListIterator_has_next(const LinkedListIterator *iterator) {
    return iterator != NULL && *iterator != NULL;
}

/**
 * Return the next value from the given LinkedListIterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a LinkedList. C'est la vie.
 * It would be easy to allow it and signal `no such element' some other way...
 */
void *
LinkedListIterator_next(LinkedListIterator *iterator) {
    if (iterator == NULL || *iterator == NULL) {
	return NULL;
    } else {
	void *data = (*iterator)->data;
	*iterator = (*iterator)->next;
	return data;
    }
}

/**
 * Print the given LinkedList to stdout, assuming that the values are
 * all null-terminated strings.
 */
void
LinkedList_print_string_list(LinkedList *list) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	printf("%s", node->data);
	if (node->next != NULL) {
	    printf(" ");
	}
    }
    printf("\n");
}
