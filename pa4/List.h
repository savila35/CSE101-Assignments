//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa4
// List.h
// Header file for List ADT
//------------------------------------------------------------------------------

#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define FORMAT "%p" // format string for List Element

// Exported types -------------------------------------------------------------
typedef void* ListElement;
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Creates and returns a new empty List.
List newList(void);

// freeList()
// Frees all memory associated with *pL, and sets *pL to NULL.
void freeList(List* pL);

// Access functions ---------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// front()
// Returns front element of L. Pre: length()>0
ListElement front(List L);

// back()
// Returns back element of L. Pre: length()>0
ListElement back(List L);

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
ListElement get(List L);


// manipulation procedures ----------------------------------------------------

// clear()
// resets l to its original empty state.
void clear(List l);

// set()
// overwrites the cursor element’s data with x. pre: length()>0, index()>=0
void set(List l, ListElement x);

// moveFront()
// if l is non-empty, sets cursor under the front element, otherwise does 
// nothing.
void moveFront(List l);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does
// nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front
// of L; it cursor is undefined do nothing.
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the back
// of L; if cursor is defined and at back, cursor becomes undefined; if cursor
// is undefined do nothing.
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before 
// front element.
void prepend(List L, ListElement x);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after 
// back element.
void append(List L, ListElement x);

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0.
void insertBefore(List L, ListElement x);

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, ListElement x);

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L);


// Other operations ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// concatList()
// // Returns a new List which is the concatenation of A and B. The cursor in the
// // new list is undefined, regardless of the states of the cursors in A and B.
// // The states of A and B are unchanged.
List concatList(List A, List B);

#endif
