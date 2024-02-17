//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa4
// MatrixTest.c
// Tests for matrix ADT implementation
//------------------------------------------------------------------------------

#include "Matrix.h"

int main(void) {
	
	//change entry test
	Matrix A = newMatrix(10);
	changeEntry(A, 2, 1, 2);
	changeEntry(A, 3, 1, 5);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 5);
	changeEntry(A, 1, 1, 4);
	changeEntry(A, 2, 2, 2);
	changeEntry(A, 2, 5, 0);
	changeEntry(A, 2, 3, 0);
	changeEntry(A, 3, 3, 5);
	if (NNZ(A) != 7)
		printf("1: %d != 7\n",NNZ(A));
	changeEntry(A, 1, 3, 0);
	changeEntry(A, 3, 1, 0);
	changeEntry(A, 3, 3, 0);
	if (NNZ(A) != 4)
		printf("2: %d != 4\n",NNZ(A));
	changeEntry(A, 7, 6, 42);
	changeEntry(A, 10, 1, 24);
	if (NNZ(A) != 6)
		printf("3: %d != 6\n",NNZ(A));
	changeEntry(A, 7, 6, 0);
	if (NNZ(A) != 5)
		printf("4: %d != 5\n",NNZ(A));
	makeZero(A);
	changeEntry(A, 5, 5, 5);
	if (NNZ(A) != 1)
		printf("5: %d != 1\n",NNZ(A));

	// diff
	makeZero(A);
	Matrix B = newMatrix(10);
	changeEntry(A, 1, 1, -4);
	changeEntry(A, 1, 2, -2);
	changeEntry(A, 1, 3, 0);
	changeEntry(A, 2, 5, 4);
	changeEntry(A, 2, 1, -2);
	changeEntry(A, 3, 1, 2);
	changeEntry(A, 2, 2, -2);
	changeEntry(A, 3, 3, 0);
	Matrix C = diff(A, A);
	if (NNZ(C) != 0 || NNZ(A) != 6)
		printf("1: pC: %d != 0 or A: %d != 6\n",NNZ(C), NNZ(A));
	changeEntry(B, 1, 1, -4);
	changeEntry(B, 1, 2, 0);
	changeEntry(B, 2, 1, 0);
	changeEntry(B, 2, 2, -2);
	changeEntry(B, 2, 4, 2);
	changeEntry(B, 3, 1, 2);
	changeEntry(B, 3, 2, 2);
	changeEntry(B, 7, 8, 5);
	Matrix D = diff(A, B);
	if (NNZ(D) != 6)
		printf("2: pD: %d != 6 or A: %d != 6\n",NNZ(D), NNZ(A));

	// product

	makeZero(A);
	makeZero(B);
	makeZero(C);
	makeZero(D);
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 2, 2, 1);
	changeEntry(A, 3, 3, 1);
	freeMatrix(&C);
	C = product(A, A);
	if (NNZ(C) != 3)
		printf("1: %d != 3\n", NNZ(A));
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 3);
	changeEntry(A, 2, 1, 4);
	changeEntry(A, 2, 2, 5);
	changeEntry(A, 2, 3, 6);
	changeEntry(A, 3, 1, 7);
	changeEntry(A, 3, 2, 8);
	changeEntry(A, 3, 3, 9);
	changeEntry(B, 1, 1, 1);
	changeEntry(B, 2, 2, 1);
	freeMatrix(&D);
	D = product(A, B);
	if (NNZ(D) != 6)
		printf("2: %d != 6\n", NNZ(D));

	// equals
	makeZero(A);
	makeZero(B);
	freeMatrix(&C);
	C = newMatrix(15);
	changeEntry(A, 1, 1, 1);
	changeEntry(C, 1, 1, 1);
	if (equals(A, C))
		  printf("1\n");
	freeMatrix(&D);
	D = newMatrix(15);
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 1, 3, 1);
	changeEntry(B, 1, 1, 1);
	changeEntry(B, 1, 3, 1);
	if (!equals(A, B))
		  printf("2\n");
	changeEntry(A, 1, 3, 0);
	if (equals(A, B))
		  printf("3\n");
	changeEntry(A, 1, 1, 0);
	makeZero(B);
	changeEntry(A, 10, 10, 10);
	changeEntry(B, 10, 10, 10);
	if (!equals(A, B))
		  printf("4\n");
	
	makeZero(A);
	makeZero(B);
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 1, 2, 2);
	changeEntry(A, 1, 3, 3);
	changeEntry(A, 2, 1, 1);
	changeEntry(A, 2, 2, 2);
	changeEntry(A, 2, 3, 3);
	changeEntry(B, 1, 1, 1);
	changeEntry(B, 1, 2, 2);
	changeEntry(B, 1, 3, 3);
	changeEntry(B, 2, 1, 1);
	changeEntry(B, 2, 2, 2);
	changeEntry(B, 2, 3, 3);
	Matrix E = product(A,B);
	assert(NNZ(E) == 6);
	makeZero(B);
	freeMatrix(&E);
	E = product(A,B);
	assert(NNZ(E) == 0);
	Matrix F = copy(A);
	assert(equals(A,F));
	printMatrix(stdout,A);

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	return 0;
}
