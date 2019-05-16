// Jonathan Kraft 05.16.19
//
// Vector.c
//
// Source File for a Dynamically-Sized Array (a.k.a Vector)

#include "Vector.h"

struct vector {
	int *array;
	int end;
};

// ***** Private Functions *****

// Pull the 0th index of the array which stores the size of the vectora
static int getSize (Vector v) {
	return (v->array[0]);
}

// Creates a new array, double the size of the old array, and copy over
// all the values
static void resize (Vector v) {
	// Create a new array twice the size of the old array
	int oldSize = getSize (v);
	int *new = malloc (2 * oldSize * sizeof (int));
	// Write in the new size in the 0th index and copy over the other elements
	new[0] = 2 * oldSize;
	for (int i = 1; i < oldSize; i++)
		new[i] = v->array[i];
	// Free the old array and set the pointer to the new array
	free (v->array);
	v->array = new;
}

// ***** Public Functions *****

// Set the vector at the given pointer to be a vector struct with 
// an array of initial size 8
void createNew (Vector *vptr) {
	*vptr = malloc (sizeof (struct vector));
	(*vptr)->array = malloc (8 * sizeof (int));
	(*vptr)->array[0] = 8;
	(*vptr)->end = 1;
}

// Append the value x to the end of the vector, expanding the size
// of the vector if necessary
void appendX (Vector v, int x) {
	// If we're out of space, double the size
	if (v->end == getSize (v))
		resize (v);
	int end = v->end;
	v->array[end] = x;
	v->end++;
}

// Set the specified location to the integer x and return true.  Print
// a message to stderr and return false if loc is 0, negative, or a 
// value beyond the end of the vector
bool setLocValue (Vector v, int loc, int x) {
	if ((loc <= 0) || (loc >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	v->array[loc] = x;
	return true;
}

// Copy the value at a specified location into the iptr address and
// return true.  Return false and set the iptr address to 0 if the
// location is 0, negative, or beyond the end of the vector
bool peekLoc (Vector v, int loc, int *iptr) {
	if ((loc <= 0) || (loc >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	*iptr = v->array[loc];
	return true;
}

// Swap the values at the given locations and return true.  Return false
// if either location is 0, negative, or beyond the end of the vector
bool swapLocs (Vector v, int loc1, int loc2) {
	if ((loc1 <= 0) || (loc2 <= 0) || (loc1 >= v->end) || (loc2 >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	int temp = v->array[loc1];
	v->array[loc1] = v->array[loc2];
	v->array[loc2] = temp;
	return true;
}

// Print all values in the vector
void printAll (Vector v) {
	for (int i = 1; i < v->end; i++)
		printf ("%d\n", v->array[i]);
}

// Print all vector indices between the start and end bounds. (The start
// value is an inclusive bound, the end value is an exclusive bound.)
void printFrom (Vector v, int start, int end) {
	// If the bounds do not intersect with any vector values, return
	if ((start >= v->end) || (end <= 0) || (start >= end))
		return;
	// Adjust start and end if necessary
	if (start <= 0)
		start = 1;
	if (end > v->end)
		end = v->end;
	// Print the values
	for (int i = start; i < end; i++)
		printf ("%d\n", v->array[i]);
}

// Free all storage occupied by the vector and set the pointer to null
void deleteAll (Vector *vptr) {
	free ((*vptr)->array);
	free (*vptr);
	*vptr = NULL;
}

// Print the data in the vector and free all storage
void dump (Vector *vptr) {
	printAll (*vptr);
	deleteAll (vptr);
}
