// Jonathan Kraft 04.29.19
//
// BalancedBST.c
//
// Source file for an AVL Tree (a.k.a. Balanaced Binary Search Tree)

#include "BalancedBST.h"
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// The Tree data type is a pointer to the root node of a balanced binary
// search tree.  In addtion to the data value stored at each node, the 
// height of the node is also kept for ease and speed of rebalanceing, 
// and of course two pointers to the left and right subtrees
struct node {
    int data, height;
    struct node *L, *R;
};

// ***** Private Functions *****

// Malloc a leaf node with x as its data value
static Tree makeLeaf (int x) {
    Tree t = malloc (sizeof (struct node));
    t->data = x;
    t->height = 0;
    t->L = NULL;
    t->R = NULL;
    return t;
}

// Perform a rotation to bring t->R up to be the root; return the new tree
static Tree leftRotate (Tree t) {
    Tree temp = t->R;
    t->R = temp->L;
    t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
    temp->L = t;
    temp->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
    return temp;
}

// Perform a rotation to bring t->L up to be the root; return the new tree
static Tree rightRotate (Tree t) {
    Tree temp = t->L;
    t->L = temp->R;
    t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
    temp->R = t;
    temp->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
    return temp;
}

// Compare heights of subtrees to determine what rotations are necessary.
// Perform the necessary rotations and return the new balanced tree.
static Tree rebalance (Tree t) {
    // Rotations when left taller than right
    if ((treeHeight (t->L) - treeHeight (t->R)) > 1) {
        // Single Rotation
        if (treeHeight (t->L->L) >= treeHeight (t->L->R)) 
            t = rightRotate (t);
        // Double Rotation
        else {
            t->L = leftRotate (t->L);
            t = rightRotate (t);
        }
    }
    // Rotations when right taller than left
    else if ((treeHeight (t->R) - treeHeight (t->L)) > 1) {
        // Single Rotation
        if (treeHeight (t->R->R) >= treeHeight(t->R->L)) 
            t = leftRotate (t);
        // Double Rotation
        else {
            t->R = rightRotate (t->R);
            t = leftRotate (t);
        }
    }
    return t;
}

// Set the tptr address to be the to largest node in t and delete that node; 
// return the modified tree
static Tree deleteLargest (Tree t, Tree *tptr) {
    // Set the tptr address to be the root if there is no right subtree
    if (t->R == NULL) {
        *tptr = t;
        return t->L;
    } 
    // Else recursively find the largest from the right subtree
    // Rebalance and recalculate heights if necessary
    else {
        t->R = deleteLargest (t->R, tptr);
        t = rebalance (t);
        t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
        return t;
    }
}

// Delete the root of the tree by either promoting a child if possible 
// or else deleting its predecessor node (always a leaf) and replacing 
// the root's data value with the predecessor's data value
static Tree deleteRoot (Tree t) {
    // Case 1: No left child, promote right child
    if (t->L == NULL) 
        return t->R;
    // Case 2: No right child, promote left child             
    if (t->R == NULL) 
        return t->L;        
    // Case 3: Two children, delete predessor and adopt its data value                                  
    Tree new;
    t->L = deleteLargest (t->L, &new);
    new->L = t->L;
    new->R = t->R;
    new = rebalance (new);
    new->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
    free (t);
    return new;
}

// ***** Public Functions *****

// Create an empty tree and return it
Tree createNew (void) {
    return NULL;
}

// Insert the value x into the tree and then return the larger tree
Tree insertX (Tree t, int x) {
    // When we reach a null location, add the leaf here
    if (t == NULL) 
        return makeLeaf (x);
    // Recursively insert x into the left subtree, perform necessary rebalances, and
    // recalculate the height of the root
    else if (x <= t->data) {
        t->L = insertX (t->L, x);
        t = rebalance (t);
        t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
        return t;
    } 
    // Recursively insert x into the right subtree, perform necessary rebalances, and
    // recalculate the height of the root
    else {
        t->R = insertX (t->R, x);
        t = rebalance (t);
        t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
        return t;
    }
}

// Delete the value x from tree if it is present, freeing its storage and return
// modified tree
Tree deleteX (Tree t, int x) {
    // If we reach a null location, the value is not present
    if (t == NULL) 
        return t;
    // Recursively search for x in the left subtree to delete it; perform 
    // necessary rebalances, and recalculate the height of the root
    else if (x < t->data) {
        t->L = deleteX (t->L, x);
        t = rebalance (t);
        t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
        return t;
    } 
    // Recursively search for x in the right subtree to delete it; perform 
    // necessary rebalances, and recalculate the height of the root
    else if (x > t->data) {
        t->R = deleteX (t->R, x);
        t = rebalance (t);
        t->height = 1 + MAX (treeHeight (t->L), treeHeight (t->R));
        return t;
    } 
    // The value is located in the root, so it must be deleted
    else {
        t = deleteRoot (t);
        return t;
    }
}

// Destroy a tree and free all of its storage; return an empty tree
Tree deleteAll (Tree t) {
    if (t == NULL) 
        return t;
    t->L = deleteAll (t->L);
    t->R = deleteAll (t->R);
    free (t);
    t = NULL;
    return t;
}

// Print all values in the tree in preorder with respect to the structure
void preorder (Tree t) {
    if (t == NULL) 
        return;
    printf ("%d\n", t->data);
    preorder (t->L);
    preorder (t->R);
}

// Print all values in the tree in ascending order
void inorder (Tree t) {
    if (t == NULL) 
        return;
    inorder (t->L);
    printf ("%d\n", t->data);
    inorder (t->R);
}

// Print all values in the tree in postorder with respect to the structure
void postorder (Tree t) {
    if (t == NULL)
        return;
    postorder (t->L);
    postorder (t->R);
    printf ("%d\n", t->data);
}

// Return number of nodes in the tree
int treeSize (Tree t) {
    if (t == NULL) 
        return 0;
    return (1 + treeSize (t->L) + treeSize (t->R));
}

// Return the total height of the tree
int treeHeight (Tree t) {
    if (t == NULL) 
        return -1;
    return t->height;
}

// Return the internal path length of the tree
int treeIPL (Tree t) {
    if (t == NULL) 
        return 0;
    if ((t->R == NULL) && (t->L == NULL)) 
        return 0;
    return (treeIPL (t->L) + treeIPL (t->R) + treeSize (t->L) + treeSize (t->R));
}
