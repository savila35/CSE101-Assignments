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
// Overwrites the cursor element's data with x. Pre: length()>0, index()>=0
void set(List L, int x) {
	if (length(L) <= 0) {
		printf("List Error: calling set() on empty list\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling set() on undefinded cursor\n");
		exit(EXIT_FAILURE);
	}	
	L->cursor->data = x;
	return;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does 
// nothing.
void moveFront(List L) {
	if (length(L) <= 0) {
		return;
	}
	L->cursor = L->front;
	L->cursorIndex = 0;
	return;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does 
// nothing.
void moveBack(List L) {
	if (length(L) <= 0) {
		return;
	}
	L->cursor = L->back;
	L->cursorIndex = length(L) - 1;
	return;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front
// of L; if cursor is defined and at front, cursor becomes undefined; if cursor
// is undefined do nothing.
void movePrev(List L) {
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->front) {
		L->cursor = NULL;
		L->cursorIndex = -1;
	} else {
		L->cursor = L->cursor->previous;
		L->cursorIndex--;
	}
	return;
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back
// of L; if cursor is defined and at back, cursor becomes undefined; if cursor
// is undefined do nothing.
void moveNext(List L) {
	if (L->cursor == NULL) {
		return;
	}
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->cursorIndex = -1;
	} else {
		L->cursor = L->cursor->next;
		L->cursorIndex++;
	}
	return;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before
// front element.
void prepend(List L, int x) {
	Node N = newNode(x);
	if (length(L) > 0) {
		L->front->previous = N;
		N->next = L->front;
		L->front = N;
		if (L->cursorIndex >= 0) {
			L->cursorIndex++;
		}
	} else {
		L->front = N;
		L->back = N;
	}
	L->length++;
	return;
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after
// back element.
void append(List L, int x) {
	Node N = newNode(x);
	if (length(L) > 0) {
		L->back->next = N;
		N->previous = L->back;
		L->back = N;
	} else {
		L->front = N;
		L->back = N;
	}	
	L->length++;
	return;
}

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
	Node N = newNode(x);
	if (length(L) <= 0) {
		printf("List Error: calling insertBefore() on empty list\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling insertBefore() on undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->front) {
		L->front = N;
		N->next = L->cursor;
		L->cursor->previous = N;
		L->cursorIndex++;
	} else {
		N->previous = L->cursor->previous;
		L->cursor->previous->next = N;
		N->next = L->cursor;
		L->cursor->previous = N;
	}
	L->length++;
	return;
}

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
	Node N = newNode(x);
	if (length(L) <= 0) {
		printf("List Error: calling insertAfter() on empty list\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling insertAfter() on undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	if (L->cursor == L->back) {
		L->back = N;
		N->previous = L->cursor;
		L->cursor->next = N;
	} else {
		L->cursor->next->previous = N;
		N->next = L->cursor->next;
		N->previous = L->cursor;
		L->cursor->next = N;
	}
	L->length++;
	return;
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
	if (length(L) <= 0) {
		printf("List Error: calling deleteFront() on empty list\n");
		exit(EXIT_FAILURE);
	}
	Node n = L->front;
	L->front = L->front->next;
	L->front->previous = NULL;
	freeNode(&n);
	if (L->cursorIndex >= 0) {
		L->cursorIndex--;
	}
	L->length--;
	return;
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
	if (length(L) <= 0) {
		printf("List Error: calling deleteBack() on empty list\n");
		exit(EXIT_FAILURE);
	}
	Node n = L->back;
	if (L->cursor == L->back) {
		L->cursor = NULL;
		L->cursorIndex = -1;
	}
	L->back = L->back->previous;
	L->back->next = NULL;
	freeNode(&n);
	L->length--;
	return;
}

// delete()
// Delete cursor element, making cursor undefinded. Pre: length>0, index()>=0
void delete(List L) {
	if (length(L) <= 0) {
		printf("List Error: calling delete() on empty list\n");
		exit(EXIT_FAILURE);
	}
	if (index(L) < 0) {
		printf("List Error: calling delete() on undefined cursor\n");
		exit(EXIT_FAILURE);
	}
	Node n = L->cursor;
	L->cursor->previous->next = L->cursor->next;
	L->cursor->next->previous = L->cursor->previous;
	freeNode(&n);
	L->cursor = NULL;
	L->cursorIndex = -1;
	L->length--;
	return;
}
	

// Other operations ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L) {
	Node n = L->front;
	while (n != NULL) {
		printf(FORMAT " ", n->data);
		n = n->next;
	}
}

// copyList()
// Returns a new List representing the same integer sequence as L. The cursor in
// the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged.
List copyList(List L) {
	List copy = newList();
	Node n = L->front;
	while (n != NULL) {
		append(copy, n->data);
		n = n->next;
	}
	return(copy);
}
	
