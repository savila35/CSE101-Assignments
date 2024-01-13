//------------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdool.h>
#include "List.h"



// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct Nodeobj {
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
} Listobj;



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
	cursorIndex = -1;
	int length = 0;
}

// freeList()
// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List* pL) {
	if (pL != NULL && *pL != NULL) {
		//free all nodes somehow
	}
	free(pL);
	*pL = NULL;
}
