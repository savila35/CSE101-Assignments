#include <stdio.h>
#include "List.h"

int main(void) {
	List list1 = newList();
	freeList(&list1);
	return(0);
}
