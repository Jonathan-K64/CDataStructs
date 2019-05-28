// Jonathan Kraft 05.16.19
//
// Vector.c
//
// Source File for a Dynamically-Sized Array (a.k.a Vector)

#include "Vector.h"

// The Vector data type is a pointer to a struct containing a pointer to the 
// first element in the array as well as information about how much space
// has been allocated for the array and the first address for appending
struct vector {
	int size, end;
	int *array;
};

// ***** Private Functions *****

// Takes an array and its size and performs an in-place O(nlogn) amortized
// quicksort algorithm
static void quickSort (int *array, int arrSize) {
	// If the size of the array is 1 or less, it must already be sorted
	if (arrSize <= 1)
		return;
	// Arbitrarily choose element 0 as the splitter
	int bound = 0;
	int temp;
	for (int i = 1; i < arrSize; i++)
		// If the value is below the splitter, increase the bound by 1
		// and swap the value with the element at that bound index
		if (array[i] < array[0]) {
			temp = array[i];
			array[i] = array[(++bound)];
			array[bound] = temp;
		}
	// Swap the splitter with the bound index
	temp = array[0];
	array[0] = array[bound];
	array[bound] = temp;
	// Recursively sort the split groups
	quickSort (array, bound);
	quickSort (array + bound + 1, arrSize - bound - 1);
}

// ***** Public Functions *****

// Set the vector at the given pointer to be a vector struct with 
// an array of initial size 8
void createNew (Vector *vptr) {
	*vptr = malloc (sizeof (struct vector));
	(*vptr)->array = malloc (8 * sizeof (int));
	(*vptr)->size = 8;
	(*vptr)->end = 0;
}

// Append the value x to the end of the vector, expanding the size
// of the vector if necessary
void appendX (Vector v, int x) {
	// If we're out of space, double the size
	if (v->end == v->size) {
		v->array = realloc (v->array, 2 * v->size * sizeof (int));
		v->size *= 2;
	}
	int end = v->end;
	v->array[end] = x;
	v->end++;
}

// Set the specified location to the integer x and return true.  Print
// a message to stderr and return false if loc is negative or a value 
// beyond the end of the vector
bool setLocValue (Vector v, int loc, int x) {
	if ((loc < 0) || (loc >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	v->array[loc] = x;
	return true;
}

// Copy the value at a specified location into the iptr address and
// return true.  Return false and set the iptr address to 0 if the
// location is negative or a value beyond the end of the vector
bool peekLoc (Vector v, int loc, int *iptr) {
	if ((loc < 0) || (loc >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	*iptr = v->array[loc];
	return true;
}

// Swap the values at the given locations and return true.  Return false
// if either location is negative or a value beyond the end of the vector
bool swapLocs (Vector v, int loc1, int loc2) {
	if ((loc1 < 0) || (loc2 < 0) || (loc1 >= v->end) || (loc2 >= v->end)) {
		fprintf (stderr, "Invalid location\n");
		return false;
	}
	int temp = v->array[loc1];
	v->array[loc1] = v->array[loc2];
	v->array[loc2] = temp;
	return true;
}

// Sort all the values in the vector using quickSort
void vectorSort (Vector v) {
	quickSort (v->array, v->end);
}

// Print all values in the vector
void printAll (Vector v) {
	for (int i = 0; i < v->end; i++)
		printf ("%d\n", v->array[i]);
}

// Print all vector indices between the start and end bounds. (The start
// value is an inclusive bound, the end value is an exclusive bound.)
void printRange (Vector v, int start, int end) {
	// If the bounds do not intersect with any vector values, return
	if ((start >= v->end) || (end <= 0) || (start >= end))
		return;
	// Adjust start and end if necessary
	if (start < 0)
		start = 0;
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
}

// Print the data in the vector and free all storage
void dump (Vector *vptr) {
	printAll (*vptr);
	deleteAll (vptr);
}
