// Jonathan Kraft 05.16.19
//
// Vector.h
//
// Header File for a Dynamically-Sized Array (a.k.a Vector)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Vector data structure
typedef struct vector *Vector;

// Set the vector at the given pointer to be a vector struct with 
// an array of initial size 8
void createNew (Vector *vptr);

// Append the value x to the end of the vector, expanding the size
// of the vector if necessary
void appendX (Vector v, int x);

// Set the specified location to the integer x and return true.  Print
// a message to stderr and return false if loc is 0, negative, or a 
// value beyond the end of the vector
bool setLocValue (Vector v, int loc, int x);

// Copy the value at a specified location into the iptr address and
// return true.  Return false and set the iptr address to 0 if the
// location is 0, negative, or beyond the end of the vector
bool peekLoc (Vector v, int loc, int *iptr);

// Swap the values at the given locations and return true.  Return false
// if either location is 0, negative, or beyond the end of the vector
bool swapLocs (Vector v, int loc1, int loc2);

// Sort all the values in the vector using quickSort
void vectorSort (Vector v);

// Print all values in the vector
void printAll (Vector v);

// Print all vector indices between the start and end bounds. (The start
// value is an inclusive bound, the end value is an exclusive bound.)
void printRange (Vector v, int start, int end);

// Free all space occupied by the vector and set the pointer to null
void deleteAll (Vector *vptr);

// Print the data in the vector and free all storage
void dump (Vector *vptr);
