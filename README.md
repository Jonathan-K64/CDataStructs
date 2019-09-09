# CDataStructs

This is a repository for several useful ADTs and corresponding header files implemented in C for use in more complex programs.  All memory allocation and destruction is included, along with many methods that might be useful when utilizing them.  Most of the structs are implemented to hold integer data but can be easily adapted to hold strings, characters, floating points, etc.

To use any of these ADTs, save duplicates of both the corresponding header and source files in the directory of interest.  #Include the header file at the top of your original code.  In your Makefile, link the header file to your program's executable, link an ADT executable file to both the header and source for the ADT, and then link your full program to both of these executables.

The current ADTs are a singly-linked list, a deque (which combines functionality of both a stack and queue) implemented using a circularly-linked list, a balanced binary search tree (that balances based on the specifications for an AVL tree), a vector array (that gets automatically reallocated to larger size as necessary), and a max heap (which is implemented using a vector array).
