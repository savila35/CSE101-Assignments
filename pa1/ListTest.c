//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa1
// ListTest.c
// Test client for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <assert.h>
#include "List.h"

int main(void) {
	List list1 = newList();
	List list2 = newList();
	
	assert(equals(list1, list2));

	append(list1, 2);
	prepend(list2, 2);
	assert(length(list1) == 1);
	assert(equals(list1, list2));

	append(list1, 2);
	assert(length(list1) == 2);
	assert(!equals(list1, list2));
	
	List list3 = copyList(list1);
	assert(equals(list3, list1));
	
	List list4 = concatList(list1, list2);
	printf("List4: ");
	printList(stdout, list4);
	printf("\n");
	
	clear(list3);
	for (int i = 0; i < 10; i++) {
		append(list3, i);
	}
	printf("List3: ");
	printList(stdout, list3);
	printf("\n");

	moveFront(list3);
	assert(length(list3) == 10);
	assert(index(list3) == 0);
	assert(get(list3) == 0);
	for (int j = 10; j > 0; j--) {
		set(list3, j);
		moveNext(list3);
	}

	moveBack(list3);
	movePrev(list3);
	movePrev(list3);
	insertBefore(list3, 11);
	insertAfter(list3, 12);
	assert(length(list3) == 12);
	assert(index(list3) == 8);
	assert(get(list3) == 3);
	

	moveFront(list3);
	deleteFront(list3);

	//get(list3);

	moveBack(list3);
	deleteBack(list3);

	moveNext(list3);
	moveFront(list3);
	delete(list3);
	//get(list3);

	clear(list1);
	clear(list2);

	prepend(list1, 1);
	prepend(list2, 1);
	prepend(list1, 2);
	prepend(list2, 2);
	append(list1,3);
	deleteBack(list1);
	assert(equals(list1,list2));
	deleteBack(list2);

	clear(list1);

	prepend(list1, 27);
	prepend(list1, 9);
	prepend(list1, 978);
	prepend(list1, 102);
	moveBack(list1);
	insertBefore(list1, 12);
	assert(index(list1) == 4);
	prepend(list1, 7);
	prepend(list1, 22222);
	prepend(list1, 14);
	moveFront(list1);
	insertBefore(list1, 67);
	assert(index(list1) == 1);

	clear(list1);
	
	prepend(list1, 1);
	prepend(list2, 1);
	prepend(list1, 2);
	prepend(list1, 2);
	moveBack(list1);
	delete(list1);
	assert(!equals(list1, list2));
	moveBack(list2);
	delete(list2);
	assert(!equals(list1, list2));
	append(list1, 3);
	append(list2, 3);
	moveBack(list1);
	delete(list1);
	moveBack(list2);
	delete(list2);
	assert(!equals(list1, list2));

	freeList(&list1);
	freeList(&list2);
	freeList(&list3);
	freeList(&list4);

	return(0);
}
