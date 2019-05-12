// Jonathan Kraft 05.11.19
//
// Deque.c
//
// Source File for Basic Stack and Queue Functions using a Circularly-Linked List

#include "Deque.h"

// The Deque data type is a pointer to the tail of a singly- and circularly-
// linked list with an integer data field (or a NULL pointer if the deque 
// is empty)
struct node {
	int data;
	struct node * next;
};
struct deque {
	struct node * tail;
};

// Create a new empty deque struct on a pointer. Returns true unless
// malloc fails, in which case it returns false.
void createNew (Deque *dptr) {
    *dptr = malloc (sizeof (struct deque));						                
    (*dptr)->tail = NULL;
}

// Add a value x to the tail of the deque
void addX (Deque *dptr, int x) {
    // If Deque is empty, create a head node, populate data info, and loop 
    // pointer to itself
    if (isEmpty (*dptr)) {
    	(*dptr)->tail = malloc (sizeof (struct node));
    	(*dptr)->tail->data = x;
    	(*dptr)->tail->next = (*dptr)->tail;
    }
    // Else attach new node to the oil tail, splice to the head, and then 
    // change the tail pointer to the new node
    else {
    	struct node *headPtr = (*dptr)->tail->next;
    	(*dptr)->tail->next = malloc(sizeof(struct node));
    	(*dptr)->tail->next->data = x;
    	(*dptr)->tail->next->next = headPtr;
    	(*dptr)->tail = (*dptr)->tail->next;
    }
}

// Add a value x to the tail of the deque
void pushX (Deque *dptr, int x) {
    // If Deque is empty, create a head node, populate data info, and loop 
    // pointer to itself
    if (isEmpty (*dptr)) {
        (*dptr)->tail = malloc (sizeof (struct node));
        (*dptr)->tail->data = x;
        (*dptr)->tail->next = (*dptr)->tail;
    }
    // Else attach new node to the oil tail and splice to the head
    else {
        struct node *headPtr = (*dptr)->tail->next;
        (*dptr)->tail->next = malloc(sizeof(struct node));
        (*dptr)->tail->next->data = x;
        (*dptr)->tail->next->next = headPtr;
    }
}

// Remove the head of the deque, deliver its data into the iptr address, and
// return true. If the deque is empty, set the iptr address to 0 and return false
bool popH (Deque *dptr, int *iptr) {
    // If Deque is empty, set the iptr address to 0 and return false
    if (isEmpty (*dptr)) {
    	(*iptr) = 0;
    	return false;
    }
    // Otherwise store the head's fields
    *iptr = (*dptr)->tail->next->data;
    struct node *secondPtr = (*dptr)->tail->next->next;
    // Check to see if this is the last element, then free it
    bool oneElt = oneElement (*dptr);
    free ((*dptr)->tail->next);
    // Either splice the strings or set the tail pointer to null if the last
    // element was just freed
    oneElt ? ((*dptr)->tail = NULL) : ((*dptr)->tail->next = secondPtr);
    return true;
}

// Check to see whether the deque struct is empty (i.e. has a null tail pointer) 
// Return true if empty and false otherwise.
bool isEmpty (Deque d) {
    return ((d->tail == NULL) ? true : false);
}

// Returns true if the deque has exactly one element in it, false otherwise
bool oneElement (Deque d) {
    return ((!isEmpty (d)) && (d->tail == d->tail->next));
}

// Returns the number of nodes in the deque
int dequeSize (Deque d) {
    int output = 0;
    if (isEmpty (d))
        return output;
    struct node *headLoc = d->tail->next;
    struct node *curr = headLoc;
    do {
        output++;
        curr = curr->next;
    } while (headLoc != curr);
    return output;
}

// Deliver the head data into the iptr address without removing it, and return 
// true. If the deque is empty, set the iptr address to 0 and return false
bool peekH (Deque d, int *iptr) {
    // If Deque is empty, produce an error message
    if (isEmpty (d)) {
        (*iptr) = 0;
        return false;
    }
    // Otherwise store the data in the iptr address and return true
    *iptr = d->tail->next->data;
    return true;
}

// Deliver the tail data into the iptr address without removing it, and return 
// true. If the deque is empty, set the iptr address to 0 and return false
bool peekT (Deque d, int *iptr) {
    // If Deque is empty, produce an error message
    if (isEmpty (d)) {
        (*iptr) = 0;
        return false;
    }
    // Otherwise store the data in the iptr address and return true
    *iptr = d->tail->data;
    return true;
}

// Print the contents of the deque in order
void printAll (Deque d) {
    if (isEmpty (d))
        return;
    struct node *headLoc = d->tail->next;
    struct node *curr = headLoc;
    do {
        printf ("%d\n", curr->data);
        curr = curr->next;
    } while (headLoc != curr);
}

// Print out the contents of each node while freeing all storage used by the
// deque.  Also sets the dptr to null
void dump (Deque *dptr) {
    // Free all nodes and print each one
    int dest;
    while (!(isEmpty (*dptr))) {
        popH (dptr, &dest);
        printf ("%d\n", dest);
    }
    // Free the deque struct and set the dptr to NULL
    free (*dptr);
    *dptr = NULL;
}

// Free all storage used by the deque and set the dptr to null
void destroyAll (Deque *dptr) {
    // Free all nodes
    int dest;
    while (!(isEmpty (*dptr)))
        popH (dptr, &dest);
    // Free the deque struct and set the dptr to NULL
    free (*dptr);
    *dptr = NULL;
}
