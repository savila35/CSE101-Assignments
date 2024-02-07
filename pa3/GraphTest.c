//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa3
// GraphTest.c
// Tests to ensure proper functionality of Graph ADT
//------------------------------------------------------------------------------

#include "Graph.h"
#include <stdio.h>

int main(void) {
	Graph A = newGraph(8);
	assert(getOrder(A) == 8);
	assert(getSize(A) == 0);
	
	addArc(A, 1, 2);
	addArc(A, 2, 3);
	addArc(A, 2, 5);
	addArc(A, 2, 6);
	addArc(A, 3, 4);
	addArc(A, 3, 7);
	addArc(A, 4, 3);
	addArc(A, 4, 8);
	addArc(A, 5, 6);
	addArc(A, 5, 1);
	addArc(A, 6, 7);
	addArc(A, 7, 6);
	addArc(A, 7, 8);
	addArc(A, 8, 8);
	addArc(A, 8, 8);
	assert(getSize(A) == 14);
	
	printGraph(stdout, A);
	List S = newList();
	for (int i=1;i<=8;i++){append(S, i);}
	DFS(A, S);
	
	int stack1[8] = {1,2,5,3,7,6,4,8};
	int discover[8] = {1,2,3,4,13,9,8,5};
	int finish[8] = {16,15,12,7,14,10,11,6};
	int c = 0;
	for (moveFront(S); index(S) >= 0; moveNext(S)) {
		assert(get(S) == stack1[c]);
		assert(getFinish(A, c+1) == finish[c]);
		assert(getDiscover(A, c+1) == discover[c]);
		c++;
	}

	Graph B = copyGraph(A);
	assert(getOrder(B) == 8);
	assert(getSize(B) == 14);
	printf("\n");
	printGraph(stdout, B);

	Graph C = transpose(A);
	assert(getOrder(C) == 8);
	assert(getSize(C) == 14);
	
	printf("\n");
	printGraph(stdout, C);
	DFS(C, S);
	int stack2[8] = {8,7,6,3,4,1,5,2};
	c = 0;
	for (moveFront(S); index(S) >= 0; moveNext(S)) {
		assert(get(S) == stack2[c]);
		c++;
	}
	assert(getParent(C, 8) == NIL);
	assert(getParent(C, 7) == NIL);
	assert(getParent(C, 3) == NIL);
	assert(getParent(C, 1) == NIL);

	Graph D = newGraph(4);
	addEdge(D,1,2);
	addEdge(D,2,3);
	addEdge(D,3,4);
	addEdge(D,4,1);
	assert(getSize(D) == 4);
	printf("\n");
	printGraph(stdout, D);

	freeGraph(&A);
	freeGraph(&B);
	freeGraph(&C);
	freeGraph(&D);
	freeList(&S);
	
	return(0);
}
