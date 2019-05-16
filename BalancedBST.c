// Jonathan Kraft 05.13.19
//
// BalancedBST.c
//
// Source file for a Balanced Binary Search Tree (a.k.a. AVL Tree)

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

// Perform a rotation to bring the node to the root of the root up to the root
static void leftRotate (Tree *tptr) {
    Tree temp = (*tptr)->R;
    (*tptr)->R = temp->L;
    (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
    temp->L = *tptr;
    temp->height = 1 + MAX (treeHeight (temp->L), treeHeight (temp->R));
    *tptr = temp;
}

// Perform a rotation to bring the node to the root of the root up to the root
static void rightRotate (Tree *tptr) {
    Tree temp = (*tptr)->L;
    (*tptr)->L = temp->R;
    (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
    temp->R = *tptr;
    temp->height = 1 + MAX (treeHeight (temp->L), treeHeight (temp->R));
    *tptr = temp;
}

// Compare heights of subtrees to determine what rotations are necessary.
// Perform the necessary rotations and return the new balanced tree.
static void rebalance (Tree *tptr) {
    // Rotations when left taller than right
    if ((treeHeight ((*tptr)->L) - treeHeight ((*tptr)->R)) > 1) {
        // Single Rotation
        if (treeHeight ((*tptr)->L->L) >= treeHeight ((*tptr)->L->R)) 
            rightRotate (tptr);
        // Double Rotation
        else {
            leftRotate (&(*tptr)->L);
            rightRotate (tptr);
        }
    }
    // Rotations when right taller than left
    else if ((treeHeight ((*tptr)->R) - treeHeight ((*tptr)->L)) > 1) {
        // Single Rotation
        if (treeHeight ((*tptr)->R->R) >= treeHeight((*tptr)->R->L)) 
            leftRotate (tptr);
        // Double Rotation
        else {
            rightRotate (&(*tptr)->R);
            leftRotate (tptr);
        }
    }
}

// ***** Public Functions *****

// Create an empty tree and return it
void createNew (Tree *tptr) {
    *tptr = NULL;
}

// Checks to see if the tree is empty, returns true if so and false otherwise
bool isEmpty (Tree t) {
    if (t == NULL)
        return true;
    else 
        return false;
}

// Checks to see if the value x is present in the tree, returns true if so
// and false otherwise
bool containsX (Tree t, int x) {
    // If we reach a null pointer, the value has not been found
    if (t == NULL)
        return false;
    // Recursively check the left subtree
    else if (x < t->data)
        return containsX (t->L, x);
    // Recursively check the right subtree
    else if (x > t->data)
        return containsX (t->R, x);
    // Else x matches the current root, so it is present
    else 
        return true;
}

// Insert the value x into the tree and then return the larger tree
void insertX (Tree *tptr, int x) {
    // When we reach a null location, malloc space for a leaf and add it here
    if (*tptr == NULL) {
        *tptr = malloc (sizeof (struct node));
        (*tptr)->data = x;
        (*tptr)->height = 0;
        (*tptr)->L = NULL;
        (*tptr)->R = NULL;
    }
    // Recursively insert x into the left subtree, perform necessary rebalances,
    // and recalculate the height of the root
    else if (x <= (*tptr)->data) {
        insertX (&(*tptr)->L, x);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
    } 
    // Recursively insert x into the right subtree, perform necessary rebalances,
    // and recalculate the height of the root
    else {
        insertX (&(*tptr)->R, x);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
    }
}

// Delete the value x from the tree if it is present, freeing its storage and return
// true, unless the value is not present in which case false is returned
bool deleteX (Tree *tptr, int x) {
    // If we reach a null location, the value is not present
    if (*tptr == NULL) 
        return false;
    // Recursively search for x in the left subtree to delete it; perform 
    // necessary rebalances, and recalculate the height of the root
    else if (x < (*tptr)->data) {
        bool output = deleteX (&(*tptr)->L, x);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
        return output;
    } 
    // Recursively search for x in the right subtree to delete it; perform 
    // necessary rebalances, and recalculate the height of the root
    else if (x > (*tptr)->data) {
        bool output = deleteX (&(*tptr)->R, x);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
        return output;
    } 
    // The value is located in the root, so it must be deleted
    else {
        deleteRoot (tptr, &x);
        return true;
    }
}

// Delete the root of the tree, freeing its storage, inputting its data 
// into the iptr address and return true, unless the tree is null in which 
// case false is returned and the iptr address is set to 0
bool deleteRoot (Tree *tptr, int *iptr) {
    // If the tree is null, set the iptr address to 0 and return false
    if (*tptr == NULL) {
        *iptr = 0;
        return false;
    }
    // If the tree is not null, input the root data into the iptr address
    *iptr = (*tptr)->data;
    // Case 1: No left child, promote right child
    if ((*tptr)->L == NULL) {
        *tptr = (*tptr)->R;
        return true;
    }
    // Case 2: No right child, promote left child             
    else if ((*tptr)->R == NULL) {
        *tptr = (*tptr)->L;
        return true;
    }
    // Case 3: Two children, delete predessor and adopt its data value                                  
    else {
        deleteMax (&(*tptr)->L, &(*tptr)->data);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
        return true;
    }
}

// Delete the largest value in the tree, freeing its storage, inputting its 
// data into the iptr address and return true.  If the tree is null, false 
// is returned instead and the iptr address is set to 0
bool deleteMax (Tree *tptr, int *iptr) {
    // If the tree is null, set the iptr address to 0 and return false
    if (*tptr == NULL) {
        *iptr = 0;
        return false;
    }
    // If there is no right subtree, the root is the max element; enter the 
    // root's data value into the iptr address and set the new root to be the
    // left subtree
    else if ((*tptr)->R == NULL) {
        *iptr = (*tptr)->data;
        Tree new = (*tptr)->L;
        free (*tptr);
        *tptr = new;
        return true;
    }
    // Else recursively find the largest from the right subtree
    // Rebalance and recalculate heights if necessary
    else {
        bool output = deleteMax(&(*tptr)->R, iptr);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
        return output;
    }
}

// Delete the smallest value in the tree, freeing its storage, inputting its 
// data into the iptr address and return true.  If the tree is null, false 
// is returned instead and the iptr address is set to 0
bool deleteMin (Tree *tptr, int *iptr) {
    // If the tree is null, set the iptr address to 0 and return false
    if (*tptr == NULL) {
        *iptr = 0;
        return false;
    }
    // If there is no left subtree, the root is the min element; enter the 
    // root's data value into the iptr address and set the new root to be the
    // right subtree
    else if ((*tptr)->L == NULL) {
        *iptr = (*tptr)->data;
        Tree new = (*tptr)->R;
        free (*tptr);
        *tptr = new;
        return true;
    }
    // Else recursively find the smallest from the left subtree
    // Rebalance and recalculate heights if necessary
    else {
        bool output = deleteMin(&(*tptr)->L, iptr);
        rebalance (tptr);
        (*tptr)->height = 1 + MAX (treeHeight ((*tptr)->L), treeHeight ((*tptr)->R));
        return output;
    }
}

// Destroy a tree and free all of its storage, leaving an empty tree
void deleteAll (Tree *tptr) {
    if (*tptr == NULL) 
        return;
    deleteAll (&(*tptr)->L);
    deleteAll (&(*tptr)->R);
    free (*tptr);
    *tptr = NULL;
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

// Destroy a tree, printing all of its data values in postorder with respect
// to the structure before freeing each node's storage
void dump (Tree *tptr) {
    if (*tptr == NULL) 
        return;
    dump (&(*tptr)->L);
    dump (&(*tptr)->R);
    printf ("%d\n", (*tptr)->data);
    free (*tptr);
    *tptr = NULL;
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
