// Jonathan Kraft 05.10.19
//
// LinkedList.c
//
// Source File for Basic Singly-Linked List Functions

#include "LinkedList.h"

// The List data type is a pointer to the head of a singly-linked list
// node containing an integer data field
struct node {
	int data;
	struct node * next;
};

// Create a new null list on a pointer
void createNew (List *lptr) {
	*lptr = NULL;
}

// Add a new value to the front of the list
void addToF (List *lptr, int x) {
	List n = malloc (sizeof (struct node));		// Make a new node
	n->data = x;			// store x in the node's data value
	n->next = *lptr;		// make the new head point to the old head
	*lptr = n;			// change the head ptr
}

// Add a new value to a specified location in the list (non-negative integer
// only).  Note: the head is enumerated loc = 0, the second element would be 
// enumerated loc = 1, etc.  If the list is long enough to accomodate this, 
// the function will return true; otherwise, the value will be added to the
// end and false is returned
bool addToLoc (List *lptr, int x, int loc) {
	// Loc is Negative: print an error and add nothing
	if (loc < 0) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	// Loc is Zero: add to front and return true always
	if (loc == 0) {
		addToF (lptr, x);
		return true;
	}
	// Loc is Positive: try to add in proper location, add to end if null reached
	List curr = *lptr;
	while (loc-- > 1) {
		if (curr->next == NULL)
			break;
		curr = curr->next;
	}
	addToF (&(curr->next), x);
	return (loc == 0);
}

// Remove the first instance of a value from the list and return true, 
// or return false if the value is not present anywhere in the list
bool deleteX (List *lptr, int x) {
	// If the list is empty, there can be nothing to erase
	if (*lptr == NULL)
		return false;
	// If the value is located in the head, change the head, return true
	if ((*lptr)->data == x) {
		List temp = (*lptr)->next;
		free (*lptr);
		*lptr = temp;
		return true;
	}
	// Otherwise, loop through the items to try to find a match
	List curr = *lptr;
	while (curr->next != NULL) {
		// If the item is found, remove its node, splice the split 
		// chains and return true
		if (curr->next->data == x) {
			List temp = curr->next->next;
			free (curr->next);
			curr->next = temp;
			return true;
		}
		curr = curr->next;
	}
	return false;
}

// Remove all instances of a value from the list and return how many nodes
// were removed
int deleteAllX (List *lptr, int x) {
	// If the list is empty, there can be nothing to erase
	if (*lptr == NULL)
		return false;
	// Create a variable to store how many matches were found
	int counter = 0;
	// If the value is located in the head, change the head
	if ((*lptr)->data == x) {
		List temp = (*lptr)->next;
		free (*lptr);
		*lptr = temp;
		counter++;
	}
	// Loop through the other items to try to find additional matches
	List curr = *lptr;
	while (curr->next != NULL) {
		// If any matches are found, remove its node, splice the chains
		if (curr->next->data == x) { 
			List temp = curr->next->next;
			free (curr->next);
			curr->next = temp;
			counter++;
		}
		// Otherwise move curr pointer to the next node
		else 
			curr = curr->next;
	}
	return counter;
}

// Iterate through the list and determine whether a value is present
bool findX (List l, int x) {
	while (l != NULL) {
		if (l->data == x)
			return true;
		l = l->next;
	}
	return false;
}

// Iterate through a list and determine what position in the list the first 
// instance of a value is located.  Note: the head is enumerated loc = 0, 
// the second element would be enumerated loc = 1, etc.  If the value is not 
// present, -1 is returned
int findXLoc (List l, int x) {
	int counter = 0;
	while (l != NULL) {
		if (l->data == x)
			return counter;
		l = l->next;
		counter++;
	}
	return -1;
}

// Determine the number of nodes there are in the list
int listSize (List l) {
	int counter = 0;
	while (l != NULL) {
		counter++;
		l = l->next;
	}
	return counter;
}

// Print every element in the list
void printAll (List l) {
	while (l != NULL) {
		printf ("%d\n", l->data);
		l = l->next;
	}
}

// Print first n elements' data from the list in order
void printN (List l, int n) {
	while ((l != NULL) && (n-- > 0)) {
		printf ("%d\n", l->data);
		l = l->next;
	}
}

// Print every elements' data from the list in order.  If x is ever found, stop
// and return true; otherwise, print the whole list and then return false
bool printToX (List l, int x) {
	while (l != NULL) {
		printf ("%d\n", l->data);
		if (l->data == x)
			return true;
		l = l->next;
	}
	return false;
}

// Print each element and then clear it from memory
void dump (List *lptr) {
	while (*lptr != NULL) {
		printf ("%d\n", (*lptr)->data);
		List temp = (*lptr)->next;
		free (*lptr);
		*lptr = temp;
	}
}

// Free all storage from a list and make it null
void freeAll (List * lptr) {
	while (*lptr != NULL) {
		List temp = (*lptr)->next;
		free (*lptr);
		*lptr = temp;
	}
}
