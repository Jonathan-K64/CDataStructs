// Jonathan Kraft 05.18.19
//
// MaxHeap.h
//
// Header File for a Max Heap Priority Queue Using a Dynamically-
// Sized Array

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Heap data structure
typedef struct heap *Heap;

// Set the heap at the given pointer to be a heap struct with 
// an array of initial size 8
void createNew (Heap *hptr);

// Tests to see if the heap is empty or not; returns true if the first open
// address is the root and returns false otherwise
bool isEmpty (Heap h);

// Insert the value x to the end of the heap, allocating more memory if 
// necessary, and reorder elements
void insertX (Heap h, int x);

// Delete the max value from the heap, insert its value into the iptr address
// and return true.  If the heap is empty, set iptr to 0 and return false
bool deleteMax (Heap h, int *iptr);

// Take an array of values, heapify the values in a linear algorithm,
// and then set the array to be the array for the given heap
void linearHeapify (Heap h, int *array, int arrSize);

// Print all values in the heap
void printAll (Heap h);

// Print the contents of the heap in decreasing order and free all space
void dump (Heap *hptr);

// Input an array and its size and output a sorted array using a
// heap to sort the items efficiently in O(nlogn) time
int *heapSort (int *array, int arrSize);
