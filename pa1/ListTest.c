#include <stdio.h>
#include "List.h"

int main(void) {
	List list1 = newList();
	List list2 = newList();
	
	printf("%s\n", equals(list1, list2) ? "true" : "false");

	append(list1, 2);
	prepend(list2, 2);
	printf("%d\n", length(list1));
	printf("List1: ");
	printList(stdout, list1);
	printf("List2: ");
	printList(stdout, list2);
	printf("%s\n", equals(list1, list2) ? "true" : "false");

	append(list1, 2);
	printf("%d\n", length(list1));
	printf("List1: ");
	printList(stdout, list1);
	printf("List2: ");
	printList(stdout, list2);
	printf("%s\n", equals(list1, list2) ? "true" : "false");
	
	List list3 = copyList(list1);
	printf("List3: ");
	printList(stdout, list3);
	printf("%s\n", equals(list3, list1) ? "true" : "false");

	freeList(&list1);
	freeList(&list2);
	freeList(&list3);
	return(0);
}
