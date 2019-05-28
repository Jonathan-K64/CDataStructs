// Jonathan Kraft 05.18.19
//
// MaxHeap.c
//
// Source File for a Max Heap Priority Queue Using a Dynamically-
// Sized Array

#include "MaxHeap.h"

// The Heap data type is a pointer to a struct containing a pointer to the 
// root as well as information about how much space has been allocated for 
// the array and the first open address for insertion.
struct heap {
	int size, end;
	int *array;
};

// ***** Private Functions *****

// Takes the last element and swaps it with its parent until the parent
// is greater than the inserted value
static void siftUpLast (Heap h) {
	int curr = h->end - 1;
	while ((curr > 1) && (h->array[curr] > h->array[curr/2])) {
		int temp = h->array[curr];
		h->array[curr] = h->array[curr/2];
		h->array[curr/2] = temp;
		curr /= 2;
	}
}

// Takes an element and swaps it with its greater child until the element
// is greater than its children
static void siftDownIndex (Heap h, int i) {
	int child[2];
	int temp = h->array[i];
	while (i < h->end) {
		// Find out if either children are null and which is the larger child
		for (int j = 0; j < 2; j++)
			child[j] = (2 * i < h->end) ? h->array[2 * i + j] : /* SMALLEST POSSIBLE INTEGER VALUE */ -1;
		int maxI = (child[0] >= child[1]) ? 0 : 1;
		// If the parent is greater than or equal to both children, break
		if (temp >= child[maxI])
			break;
		// Otherwise switch the indices and move the "i" ptr to the child index
		h->array[i] = h->array[2 * i + maxI];
		i = 2 * i + maxI;
	}
	h->array[i] = temp;
}

// ***** Public Functions *****

// Set the heap at the given pointer to be a heap struct with 
// an array of initial size 8
void createNew (Heap *hptr) {
	*hptr = malloc (sizeof (struct heap));
	(*hptr)->array = malloc (8 * sizeof (int));
	(*hptr)->size = 8;
	(*hptr)->end = 1;
}

// Tests to see if the heap is empty or not; returns true if the first open
// address is the root and returns false otherwise
bool isEmpty (Heap h) {
	if (h->end == 1)
		return true;
	else 
		return false;
}

// Insert the value x to the end of the heap, allocating more memory if 
// necessary, and reorder elements
void insertX (Heap h, int x) {
	// If we're out of space, double the size
	if (h->end == h->size) {
		h->array = realloc (h->array, 2 * h->size * sizeof (int));
		h->size *= 2;
	}
	// Insert the value at the end
	int end = h->end;
	h->array[end] = x;
	h->end++;
	// Reorder the elements if necessary
	siftUpLast (h);
}

// Delete the max value from the heap, insert its value into the iptr address
// and return true.  If the heap is empty, set iptr to 0 and return false
bool deleteMax (Heap h, int *iptr) {
	// Handle the empty case
	if (isEmpty (h)) {
		*iptr = 0;
		return false;
	}
	// Pull the value at the root of the heap (the max value)
	*iptr = h->array[1];
	// Move the last value into the root and sift down
	int last = --h->end;
	h->array[1] = h->array[last];
	siftDownIndex (h, 1);
	return true;
}


// Take an array of values, heapify the values in a linear algorithm,
// and then set the array to be the array for the given heap
void linearHeapify (Heap h, int *array, int arrSize) {
	// Free the old array and allocate space for a 0th element, the new 
	// values, and 50% more empty slots. Update the size field
	free (h->array);
	int newSize = 1 + (arrSize * 3)/2;
	h->array = malloc (newSize * sizeof (int));
	h->size = newSize;
	// Copy all values from the input array to the new location and
	// update the end field
	for (int i = 0; i < arrSize; i++)
		h->array[i+1] = array[i];
	h->end = arrSize + 1;
	// Reorder the elements into a maxheap structure
	for (int j = arrSize/2; j >= 1; j--)
		siftDownIndex (h, j);
}

// Print all values in the heap in their tree structure
void printAll (Heap h) {
	for (int i = 1; i < h->end; i++)
		printf ("%d\n", h->array[i]);
}

// Print the contents of the heap in decreasing order and free all space
void dump (Heap *hptr) {
	// Pull max elements one-by-one
	while (!isEmpty (*hptr)) {
		int currMax;
		deleteMax (*hptr, &currMax);
		printf ("%d\n", currMax);
	}
	// Free the heap struct
	free (*hptr);
}

// Input an array and its size and output a sorted array using a
// heap to sort the items efficiently in O(nlogn) time
int *heapSort (int *array, int arrSize) {
	// Create a heap, and use it to heapify the array in linear time
	Heap h;
	createNew (&h);
	linearHeapify (h, array, arrSize);
	// Continually pull the greatest element and insert it at the back
	// of the unsorted elements
	while (!isEmpty (h)) {
		int currMax;
		deleteMax (h, &currMax);
		h->array[h->end] = currMax;
	}
	// Free the space of the heap and return a pointer to the sorted array
	int *output = h->array + 1;
	free (h);
	return output;
}
