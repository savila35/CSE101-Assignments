//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa6
// ListTest.cpp
// Tests for List ADT implementation
//------------------------------------------------------------------------------

#include "List.h"
#include <iostream>
#include <cassert>

int main() {
	List A;
	List B;
	for (long i = 0; i < 10; i++) {
		A.insertBefore(i);
		B.insertAfter(i);
	}
	assert(!(A == B));
	assert(A.position() == 10);
	assert(B.position() == 0);
	assert(A.length() == 10);
	assert(B.length() == 10);
	assert(A.front() == 0);
	assert(A.back() == 9);
	assert(B.front() == 9);
	assert(B.back() == 0);
	for (long j = 0; j < 10; j++) {
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
	assert(C.equals(B));
	std::cout << C << std::endl;
	assert(C.peekNext() == 9);
	C.setAfter(22);
	assert(C.peekNext() == 22);
	C.moveBack();
	assert(C.peekPrev() == 0);
	C.setBefore(20);
	assert(C.peekPrev() == 20);
	A.clear();
	assert(A.length() == 0);
	std::cout << A << std::endl;
	List D = C.concat(B);
	std::cout << D << std::endl;
	assert(D.findNext(20) == 10);
	assert(D.findNext(100) == -1);
	D.moveBack();
	assert(D.findPrev(8) == 11);
	assert(D.findPrev(70) == -1);
	D.moveFront();
	D.eraseAfter();
	assert(D.peekNext() == 8);
	D.moveBack();
	D.eraseBefore();
	assert(D.peekPrev() == 1);
}	
