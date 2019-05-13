// Jonathan Kraft 05.12.19
//
// BalancedBST.h
//
// Header file for an AVL Tree (a.k.a. Balanaced Binary Search Tree)

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Tree data structure
typedef struct node *Tree;

// Create an empty tree and return it
Tree createNew (void);

// Checks to see if the tree is empty, returns true if so and false otherwise
bool isEmpty (Tree t);

// Checks to see if the value x is present in the tree, returns true if so
// and false otherwise
bool containsX (Tree t, int x);

// Insert the value x into the tree and then return the larger tree
Tree insertX (Tree t, int x);

// Delete the value x from tree if it is present, freeing its storage and return
// modified tree
Tree deleteX (Tree t, int x);

// Delete the root of the tree and enter its data value into the iptr
// address
Tree deleteRoot (Tree t, int *iptr);

// Delete the maximum value within the tree and enter its data value into 
// the iptr address
Tree deleteMax (Tree t, int *iptr);

// Delete the minimum value within the tree and enter its data value into 
// the iptr address
Tree deleteMin (Tree t, int *iptr);

// Destroy a tree and free all of its storage; return an empty tree
Tree deleteAll (Tree t);

// Print all values in the tree in preorder with respect to the structure
void preorder (Tree t);

// Print all values in the tree in ascending order
void inorder (Tree t);

// Print all values in the tree in postorder with respect to the structure
void postorder (Tree t);

// Destroy a tree, printing all of its data values in postorder with respect
// to the structure before freeing each node's storage
Tree dump (Tree t);

// Return number of nodes in the tree
int treeSize (Tree t);

// Return the total height of the tree
int treeHeight (Tree t);

// Return the internal path length of the tree
int treeIPL (Tree t);
