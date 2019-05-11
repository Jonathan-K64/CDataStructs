// Jonathan Kraft 05.09.19
//
// LinkedList.h
//
// Header File for Basic Singly-Linked List Functions

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node *List;

// Create a new null list on a pointer
void createNew (List *lptr);

// Add a new value to the front of the list
void addToF (List *lptr, int x);

// Add a new value to a specified location in the list (non-negative integer
// only).  Note: the head is enumerated loc = 0, the second element would be 
// enumerated loc = 1, etc.  If the list is long enough to accomodate this, 
// the function will return true; otherwise, the value will be added to the
// end and false is returned
bool addToLoc (List *lptr, int x, int loc);

// Remove the first instance of a value from the list and return true, 
// or return false if the value is not present anywhere in the list
bool deleteX (List *lptr, int x);

// Remove all instances of a value from the list and return how many nodes
// were removed
int deleteAllX (List *lptr, int x);

// Iterate through the list and determine whether a value is present
bool findX (List l, int x);

// Iterate through a list and determine what position in the list the first 
// instance of a value is located.  Note: the head is enumerated loc = 0, 
// the second element would be enumerated loc = 1, etc.  If the value is not 
// present, -1 is returned
int findXLoc (List l, int x);

// Determine the number of nodes there are in the list
int listSize (List l);

// Print every element's data from the list in order
void printAll (List l);

// Print first n elements' data from the list in order
void printN (List l, int n);

// Print every elements' data from the list in order.  If x is ever found, stop
// and return true; otherwise, print the whole list and then return false
bool printToX (List l, int x);

// Print each element's data from the list in order and then free it from storage
void dump (List *lptr);

// Free all storage from a list and make it null
void freeAll (List *lptr);
