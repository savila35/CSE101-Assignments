#include "Graph.h"
#include <stdio.h>

int main(void) {
	Graph A = newGraph(9);
	assert(getOrder(A) == 9);
	assert(getSize(A) == 0);
	
	addArc(A, 1, 2);
	addArc(A, 1, 5);
	addArc(A, 2, 5);
	addArc(A, 4, 3);
	addArc(A, 5, 3);
	addArc(A, 5, 6);
	addArc(A, 6, 4);
	addArc(A, 7, 5);
	addArc(A, 7, 8);
	addArc(A, 8, 5);
	addArc(A, 8, 9);
	addArc(A, 9, 6);
	assert(getSize(A) == 12);
	
	List S = newList();
	for (int i=1;i<=9;i++){append(S, i);}
	DFS(A, S);
	assert(getDiscover(A, 1) == 1);
	assert(getFinish(A, 1) == 12);
	assert(front(S) == 7);	

	Graph B = copyGraph(A);

	return(0);
}
