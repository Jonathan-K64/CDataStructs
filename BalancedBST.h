// Jonathan Kraft 05.12.19
//
// BalancedBST.h
//
// Header file for a Balanced Binary Search Tree (a.k.a. AVL Tree)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Tree data structure
typedef struct node *Tree;

// Create an empty tree and return it
void createNew (Tree *tptr);

// Checks to see if the tree is empty, returns true if so and false otherwise
bool isEmpty (Tree t);

// Checks to see if the value x is present in the tree, returns true if so
// and false otherwise
bool containsX (Tree t, int x);

// Insert the value x into the tree and then return the larger tree
void insertX (Tree *tptr, int x);

// Delete the value x from the tree if it is present, freeing its storage and return
// true, unless the value is not present in which case false is returned
bool deleteX (Tree *tptr, int x);

// Delete the root of the tree, freeing its storage, inputting its data 
// into the iptr address and return true, unless the tree is null in which 
// case false is returned and the iptr address is set to 0
bool deleteRoot (Tree *tptr, int *iptr);

// Delete the largest value in the tree, freeing its storage, inputting its 
// data into the iptr address and return true.  If the tree is null, false 
// is returned instead and the iptr address is set to 0
bool deleteMax (Tree *tptr, int *iptr);

// Delete the smallest value in the tree, freeing its storage, inputting its 
// data into the iptr address and return true.  If the tree is null, false 
// is returned instead and the iptr address is set to 0
bool deleteMin (Tree *tptr, int *iptr);

// Destroy a tree and free all of its storage, leaving an empty tree
void deleteAll (Tree *tptr);

// Print all values in the tree in preorder with respect to the structure
void preorder (Tree t);

// Print all values in the tree in ascending order
void inorder (Tree t);

// Print all values in the tree in postorder with respect to the structure
void postorder (Tree t);

// Destroy a tree, printing all of its data values in postorder with respect
// to the structure before freeing each node's storage
void dump (Tree *tptr);

// Return number of nodes in the tree
int treeSize (Tree t);

// Return the total height of the tree
int treeHeight (Tree t);

// Return the internal path length of the tree
int treeIPL (Tree t);
