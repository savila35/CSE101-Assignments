//-----------------------------------------------------------------------------
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_
#include <stdbool.h>

#define FORMAT "%d" // format string for List Element

// Exported types -------------------------------------------------------------
typedef int ListElement;
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
int front(List L);

// back()
// Returns back element of L. Pre: length()>0
int back(List L);

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
int get(List L);

// equals()
// returns true iff lists a and b are in same state, and returns false 
// otherwise.
bool equals(List a, List b);


// manipulation procedures ----------------------------------------------------

// clear()
// resets l to its original empty state.
void clear(List l);

// set()
// overwrites the cursor element’s data with x. pre: length()>0, index()>=0
void set(List l, int x);

// movefront()
// if l is non-empty, sets cursor under the front element, otherwise does 
// nothing.
void movefront(List l);

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
void prepend(List L, int x);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after 
// back element.
void append(List L, int x);

// insertBefore()
// Insert new element before cursor. Pre: length()>0, index()>=0.
void insertBefore(List L, int x);

// insertAfter()
// Insert new element after cursor. Pre: length()>0, index()>=0
void insertAfter(List L, int x);

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L);

#endif
