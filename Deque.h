// Jonathan Kraft 05.11.19
//
// Deque.h
//
// Header File for Basic Stack and Queue Functions using a Circularly-Linked List

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct deque *Deque;

// Create a new empty deque struct on a pointer
void createNew (Deque *dptr);

// Add a value x to the tail of the deque
void addX (Deque *dptr, int x);

// Add a value x to the tail of the deque
void pushX (Deque *dptr, int x);

// Remove the head of the deque, deliver its data into the iptr address, and
// return true. If the deque is empty, set the iptr address to 0 and return false
bool popH (Deque *dptr, int *iptr);

// Check to see whether the deque struct is empty (i.e. has a null tail pointer) 
// Return true if empty and false otherwise.
bool isEmpty (Deque d);

// Returns true if the deque has exactly one element in it, false otherwise
bool oneElement (Deque d);

// Returns the number of nodes in the deque
int dequeSize (Deque d);

// Deliver the head data into the iptr address without removing it, and return 
// true. If the deque is empty, set the iptr address to 0 and return false
bool peekH (Deque d, int *iptr);

// Deliver the tail data into the iptr address without removing it, and return 
// true. If the deque is empty, set the iptr address to 0 and return false
bool peekT (Deque d, int *iptr);

// Print the contents of the deque in order
void printAll (Deque d);

// Print out the contents of each node while freeing all storage used by the
// deque.  Also sets the dptr to null
void dump (Deque *dptr);

// Free all storage used by the deque and set the dptr to null
void destroyAll (Deque *dptr);
