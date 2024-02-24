#include "List.h"
#include <iostream>
#include <cassert>

int main() {
	List A;
	List B;
	for (int i = 0; i < 10; i++) {
		A.insertBefore(i);
		B.insertAfter(i);
	}
	assert(!(A == B));
	assert(A.position() == 10);
	assert(B.position() == 0);
	for (int j = 0; j < 10; j++) {
		A.insertBefore(j);
	}
	A.moveFront();
	assert(A.moveNext() == 0);
	assert(A.moveNext() == 1);
	assert(A.position() == 2);
	A.insertBefore(8);
	A.insertBefore(9);
	std::cout << A << std::endl;
	A.cleanup();
	std::cout << A << std::endl;
	assert(A.position() == 4);
	List C = B;
	assert(C == B);
	std::cout << C << std::endl;
	assert(C.peekNext() == 9);
	C.moveBack();
	assert(C.peekPrev() == 0);
	
}	
