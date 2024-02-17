//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa4
// ListTest.c
// Tests for List ADT implementation
//------------------------------------------------------------------------------

#include "List.h"

int main(void) {
	List A = newList();
	List B = newList();
	int a[] = {0,1,2,3,4,5,6,7,8,9};
	
	for (int i = 0; i <= 9; i++) {
		append(A, &a[i]);
		prepend(B, &a[i]);
	}
	assert(length(A) == 10);
	assert(length(B) == 10);
	
	moveBack(B);
	for (moveFront(A); index(A) >= 0 && index(B) >= 0; moveNext(A)) {
		assert(get(A) == get(B));
		movePrev(B);
	}

	List C = newList();
	List D = newList();
	prepend(C, a);
	prepend(D, a);
	assert(front(C) == front(D));

	clear(C);
	clear(D);
	assert(length(C) == 0);
	assert(length(C) == 0);
	for (moveFront(A); index(A) >= 0; moveNext(A)) {
		append(C, get(A));
	}
	
	moveFront(C);
	assert(index(C) == 0);
	int i;
	for (i = 0; i <=2; i++) {
		moveNext(C);
	}
	assert(index(C) == 3);
	insertBefore(C, &a[9]);
	insertAfter(C, &a[9]);
	assert(index(C) == 4); 
	for (i = 0; i <=2; i++) {
		moveNext(C);
	}
	assert(index(C) == 7); 
	delete(C);
	assert(index(C) == -1); 
	assert(length(C) == 11);
	moveBack(C);
	set(C, &a[0]);
	assert(get(C) == &a[0]);
	deleteBack(C);
	assert(index(C) == -1);
	moveFront(C);
	deleteFront(C);
	assert(index(C) == -1);
	assert(length(C) == 9);
	return(0);
	
}
