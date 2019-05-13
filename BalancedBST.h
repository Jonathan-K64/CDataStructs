// Jonathan Kraft 04.29.19
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

// Insert the value x into the tree and then return the larger tree
Tree insertX (Tree t, int x);

// Delete the value x from tree if it is present, freeing its storage and return
// modified tree
Tree deleteX (Tree t, int x);

// Destroy a tree and free all of its storage; return an empty tree
Tree deleteAll (Tree t);

// Print all values in the tree in preorder with respect to the structure
void preorder (Tree t);

// Print all values in the tree in ascending order
void inorder (Tree t);

// Print all values in the tree in postorder with respect to the structure
void postorder (Tree t);

// Return number of nodes in the tree
int treeSize (Tree t);

// Return the total height of the tree
int treeHeight (Tree t);

// Return the internal path length of the tree
int treeIPL (Tree t);
