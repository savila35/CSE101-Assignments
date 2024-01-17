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
	printf("%d\n", length(list1));
	printf("List1: ");
	printList(stdout, list1);
	printf("\n");
	printf("List2: ");
	printList(stdout, list2);
	printf("\n");
	assert(equals(list1, list2));

	append(list1, 2);
	printf("%d\n", length(list1));
	printf("List1: ");
	printList(stdout, list1);
	printf("\n");
	printf("List2: ");
	printList(stdout, list2);
	printf("\n");
	assert(!equals(list1, list2));
	
	List list3 = copyList(list1);
	printf("List3: ");
	printList(stdout, list3);
	printf("\n");
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
	printf("length: %d, index: %d, cursor: %d\n", length(list3), index(list3), get(list3));
	for (int j = 10; j > 0; j--) {
		set(list3, j);
		moveNext(list3);
	}
	printf("List3: ");
	printList(stdout, list3);
	printf("\n");
	
	moveBack(list3);
	movePrev(list3);
	movePrev(list3);
	insertBefore(list3, 11);
	insertAfter(list3, 12);
	printf("List3: ");
	printList(stdout, list3);
	printf("\n");
	printf("length: %d, index: %d, cursor: %d\n", length(list3), index(list3), get(list3));

	moveFront(list3);
	deleteFront(list3);

	moveBack(list3);
	deleteBack(list3);

	moveNext(list3);
	moveFront(list3);
	delete(list3);
	printf("List3: ");
	printList(stdout, list3);
	printf("\n");
	printf("length: %d, index: %d\n", length(list3), index(list3));

	freeList(&list1);
	freeList(&list2);
	freeList(&list3);
	freeList(&list4);

	List A = newList();
	List B = newList();
	prepend(A, 1);
	prepend(B, 1);
	prepend(A, 2);
	prepend(B, 2);
	deleteBack(A);
	printf("A: ");
	printList(stdout, A);
	printf("\n");
	printf("B: ");
	printList(stdout, B);
	if (equals(A, B))
	printf("wrong\n");
	deleteBack(B);
	if (!equals(A, B))
	printf("wrong\n");
	deleteBack(B);

	clear(A);

	printf("A: ");
	printList(stdout, A);
	printf("\n");

	prepend(A, 34);
	prepend(A, 4);
	prepend(A, 354);
	prepend(A, 3674);
	printf("A: ");
	printList(stdout, A);
	printf("\n");
	moveBack(A);
	printf("A: ");
	printList(stdout, A);
	printf("\n");
	insertBefore(A, 435);
	printf("A: ");
	printList(stdout, A);
	printf("\n");
	if (index(A) != 4)
		printf("wrong1\n");
	prepend(A, 324);
	prepend(A, 33464);
	prepend(A, 3498);
	moveFront(A);
	insertBefore(A, 67);
	if (index(A) != 1)
		printf("wrong2\n");

	clear(A);
	
	prepend(A, 1);
	prepend(B, 1);
	prepend(A, 2);
	prepend(B, 2);
	moveBack(A);
	delete (A);
	if (equals(A, B))
		printf("wrong1\n");
	printf("A: ");
	printList(stdout, A);
	printf("\n");
	printf("B: ");
	printList(stdout, B);
	printf("\n");
	moveBack(B);
	printf("B: ");
	printList(stdout, B);
	printf("\n");
	delete (B);
	printf("B: ");
	printList(stdout, B);
	printf("\n");
	if (!equals(A, B))
		printf("wrong2\n");
	append(A, 3);
	append(B, 3);
	moveBack(A);
	delete (A);
	moveBack(B);
	delete (B);
	if (!equals(A, B))
		printf("wrong3\n");

	return(0);
}
