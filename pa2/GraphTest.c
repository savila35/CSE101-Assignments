//------------------------------------------------------------------------------
// Sebastian Avila
// snavila
// 2024 Winter CSE101 pa2
// GraphTest.c
// Tests for Graph ADT implementation
//-----------------------------------------------------------------------------

#include "Graph.h"
#include <stdio.h>
#include <stdbool.h>

int main(void) {
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	printGraph(stdout, G);
	
	BFS(G, 1);
	printf("Distance: %d\n", getDist(G, 5));

	Graph A = newGraph(64);
	List L = newList();
	List C = newList();
	addEdge(A, 64, 4);
	addEdge(A, 64, 3);
	addEdge(A, 42, 2);
	addEdge(A, 2, 64);
	addEdge(A, 4, 2);
	addEdge(A, 3, 42);
	BFS(A, 3);
	getPath(L, A, 64);
	append(C, 3);
	append(C, 64);
	if (!equals(L, C))
		printf("1\n");
	moveFront(L);
	BFS(A, 2);
	getPath(L, A, 2);
	append(C, 2);
	printList(stdout, L);
	printf("\n");
	printList(stdout, C);
	printf("\n");
	if (!equals(L, C))
		printf("2\n");

	return(0);
}
