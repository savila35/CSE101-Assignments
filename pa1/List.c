//------------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"



// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
	ListElement data;
	Node previous;
	Node next;
} NodeObj;

// private ListObj type
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int cursorIndex;
	int length;
} ListObj;



// Constructors-Destructors ----------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes previous, next, and data 
// fields.
Node newNode(ListElement data) {
	Node N = malloc(sizeof(NodeObj));
	assert(N != NULL);
	N->data = data;
	N->previous = NULL;
	N->next = NULL;
	return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

// newList()
// Creates and returns a new empty List
List newList(void) {
	List L = malloc(sizeof(ListObj));
	assert(L != NULL);
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->cursorIndex = -1;
	L->length = 0;
	return(L);
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		Node current = (*pL)->front;
		while(current != NULL) {
			Node nextNode = current->next;
			freeNode(&current);
			current = nextNode;
		}
		free(*pL);
		*pL = NULL;
	}
}

// Access functions ------------------------------------------------------------

// length() 
// Returns the number of elements in L.
int length(List L) {
	int len = L->length;
	return(len);
}

// index()
// Returns index of cursor element if definded, -1 otherwise.
int index(List L) {
	int index = L->cursorIndex;
	return(index);
}

// front()
// Returns front element of L. Pre: length()>0
int front(List L) {
	if (length(L) <=0 ) {
		printf("List Error: calling front() on empty list\n");
		exit(EXIT_FAILURE);
	}
	int front = L->front->data;
	return(front);
}

// back()
// Returns back element of L. Pre: length>0
int back(List L) {
	if (length(L) <=0 ) {
		printf("List Error: calling back() on empty list\n");
		exit(EXIT_FAILURE);
	}
	int back = L->back->data;
	return(back);
}

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0.
int get(List L) {
	if (length(L) <= 0) {
		printf("List Error: calling get() on empty list\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling get() on undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	int cursor = L->cursor->data;
	return(cursor);
}

// equals()
// Returns true iff Lists A and B are in same state, and returns false 
// otherwise.
bool equals(List A, List B) {
	Node a = A->front;
	Node b = B->front;
	while (a != NULL && b != NULL) {
		if (a->data != b->data) {
			return(false);
		}
		a = a->next;
		b = b->next;
	}
	if (a != NULL || b != NULL) {
		return(false);
	}
	return(true);
}



// Manipulation procedures -----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
	freeList(&L);
	L = newList();
}

// set()
